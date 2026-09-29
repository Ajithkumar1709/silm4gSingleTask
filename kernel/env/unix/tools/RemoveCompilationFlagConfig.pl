#------------------------------------------------------------
# (C) Copyright [2006-2008] Marvell International Ltd.
# All Rights Reserved
#------------------------------------------------------------

############################################################################
# RemoveCompilationFlagConfig		#08/16/2007 4:53PM
# Ron Zeira
############################################################################

# flag removal script with configuration file
# Ron Zeira
# August 2007

#use Switch;

#function delarations
sub ReadParamsFromFile($$);
sub EvaluateExpressionArray (@);
sub RemoveUndefsFromArray (@);
sub EvaluateIsDefined ($);
sub EvaluateArithmeticExpression ($);
sub EvaluateLogicalExpression ($$$$$);
sub RemoveComment ($);
sub EvaluateIfdef (@);
sub EvaluateIfndef (@);
sub StartHandlingIf ($@);
sub StartHandlingElif ($@);
sub ContinueHandlingIf($$);
sub ContinueHandlingElif($$);
sub ContinueCheckKey($$);
sub StartCheckKey($@);
sub IsIgonredFile($);
sub HasWrapingBrackets ($);
sub IsIgonredFolder($);

#start of script:

#get configuration file name
$Configuration_file = shift;

#get base folders from config
@base_folders = ReadParamsFromFile($Configuration_file,"Base Folders");

#get flags to remove
@flags_to_remove = ReadParamsFromFile($Configuration_file,"Remove These Flags");

#get other flag definitions related to this flag
# if the flag is not defined put undef as his value
%flagdefinitions = ReadFlagsFromFile($Configuration_file,"Flag DB");

#files in these list will be ignored
@IgnoredFiles = ReadParamsFromFile($Configuration_file,"Ignore These Files");

#files in these folders will be ignored
@IgnoredFolders = ReadParamsFromFile($Configuration_file,"Ignore These Folders");

#while (($one,$two) = each %flagdefinitions)
#{
#	print "$one => $two\n";
#}
#die "bla\n";

#sets updates every number of files working on
$UpdateEvery = 50;

#key words of preprocessor logic
@Keywords = ('ifdef','ifndef','elif','else','endif','if');

$path;
$flag;

#go over all the paths
foreach $path (@base_folders)
{
	#remove each flag
	foreach $flag (@flags_to_remove)
	{
		print "Start removing flag $flag from $path\n";
#general variables for statistics
		$ReadOnlyFiles = 0;
		$NumOfOpenFiles = 0;
		$NumOfFlags = 0;

# dir the desire directory
		@p = `cmd /c dir /B /S $path`;
		chomp @p;
#print "@p\n";

#counts working files
		$num_of_files = 0;

# look for files inside DIR resualts
# searches only in c\h\asm\ldf files
		foreach $file (@p) {
		  # with extention *.C *.c *.H *.h *.asm
			# support only c\h\asm\ldf files
			#print "\n file : $file\n";
			next if (IsIgonredFolder($file));
			while ($file=~/(.+\.(([cChH])|(asm)|(ldf)))$/g)
		  	{
		  	#the current file
		    $CurrentFilePath = "$1";
		   next if (IsIgonredFile($CurrentFilePath));
				#print "Working on $CurrentFilePath:\n";
				$num_of_files++;
				if (($num_of_files% $UpdateEvery) == 0)
				{
					print "scanned $num_of_files so far\n";
				}
			#opens file for reading
		      open(SOURCE_FILE, "< $CurrentFilePath") || die "\ncannot open file";
			  # initialize variables for this file
			  $NumOfFlagsInFile = 0;
			  $NumOfRemoval = 0;
			  #read file
			  @file_lines = <SOURCE_FILE>;
			  close SOURCE_FILE;
			  #go over the file until no flags to be removed
		   	  do
			  {
			  	# initialize variables for this iteration   
		      	$StartCounter = 0;
			  	$remove_line= 0;
			  	$remove_code = 0;
			  	$NumOfRemoval = 0;
			  	@lineDB = ();
			  	$line_num = 0;
			  	$current_key = '';
			  	$force_remove = 0;
			  	$encountered_elif = 0;
				$line_num=0;
				$continue_line = 0;
				$last_line ='';
				#go over the file lines
			  	while (@file_lines)
		      	{
					#concatenate line to the ilne before if ends with \
					if ($continue_line == 0 ) {
						$line = shift(@file_lines);
					}
					else
					{
						$line .= shift(@file_lines);
						$continue_line = 0;
					}
					$indent = '';
			  		$line_num ++;
			  		$data = '';
			  		$newdata = '';
			  		$remove_line = 0;
			  		chomp $line;
					#divide the data and comment in the line
					($data,$comment) = RemoveComment $line;
			  		if ( ($current_key eq '') && ($StartCounter == 0) ) { # no key
			  			# checks comments
			  	 		if ( ( $line =~ /^(\s*((\/\/)|(\/\*)))/ ) )
			  	 		{
			  				$data = '';
			  				$comment = $line;
				  		}
			  	 		else #not a comment
			  	 		{
							#check if contains the flag
			  				if ( $data =~ /\W$flag/ )
			  				{
								#check if the flag is in a question
			  					for my $key ( @Keywords )
			  					{
									#if found extract the logical expression
			  				   		if ( $data =~ /^(\s*)\#\s*$key/  )
			  				   		{
			  				   			$logical_expr = $';
										$indent = $1;
			  				   			$logical_expr =~ s/\s//g;
			  				   			@Exprs = split(/([\s,\!,\(,\)]|\&\&|\|\||\=\=|\<\=|\!\=|\>\=|\<|\>)/, $logical_expr);
			  					   		@Exprs = RemoveUndefsFromArray(@Exprs);
			  					   		$current_key = $key;
			  					   		last;
			  					 	}
			  					}
			  				}
							#in case the key was found
			  				if ( $current_key ne '' ) {
			  					#found a key
								if ( $line =~ /\\$/ ) {
					  				$line = $`;
							   		$continue_line = 1;
									$current_key = '';
									next;
				 				}
								#evaluate the logical expression according to the key
								# decides what part to remove and if the question needs to be changed
								$data = StartCheckKey($data,@Exprs);
			  				}
							else
							{
								#check if its a part of a 2 line question
								for my $key ( @Keywords )
			  					{
			  				   		if ( $data =~ /^(\s*)\#\s*$key/  )
			  				   		{
			  				   			if ( $line =~ /\\$/ ) {
					  						$line = $`;
							   	   			$continue_line = 1;
							   				$current_key = '';
								 			last;
				 			   			}
			  					 	}
			  					}
								next if ($continue_line == 1);
							}
			  			}
			  		}
			  		else # has $current_key
			  		{
			  			my $tempkey = '';
			  			my $temp = '';
						#check if line starts with a key
			  			for $temp ( @Keywords )
			  		   	{
			  		    	if ( $data =~ /^\s*\#\s*$temp/  )
			  			 	{
			  			 		$logical_expr = $';
			  			 		$logical_expr =~ s/\s//g;
			  					$tempkey = $temp;
			  			   		last;
			  			 	}
			  		 	}
						$tempkey = '' if($current_key eq '');
			  			if ( $tempkey ne '' ) {
							#check multiple line
							if ( $line =~ /\\$/ ) {
					  				$line = $`;
							   		$continue_line = 1;
									next;
				 			}
							#increment when entring if
			  				$StartCounter++ if ($tempkey =~ /^if/);
							#decrement when exiting endif
			  		   		$StartCounter-- if ($tempkey eq 'endif');
							#evaluate the situation according to the key we started
							# handling and the key found

							$data = ContinueCheckKey($data,$tempkey);
			  			}

			  		}
			  		# if we are remove code section remove this line
			  		if ( $remove_code == 1 ) {
			  				$remove_line = 1;
			  		}
		      		  # Read Source line to array
		       		  if ($remove_line == 0){
							#keep indantation and comment together with new data
			  		   		my $temp = "$indent$data$comment\n";
		      	  	 		 push @lineDB, $temp;
		      	  		}
			      	  # senety Code check
		      		  if ($StartCounter < 0){
			  	   			print "\nerror in line number $line_num";
		      	   		 die " \n **** Error: Section END with no Section Start in file $CurrentFilePath"
		      	  	  }
		       	 }
				 #copy the updated lines for next iteration
			   	 @file_lines = @lineDB;
			 }
			 while ($NumOfRemoval > 0); #keep going while there are flags
			   #we modify the file only if we found the flag inside it
				if ($NumOfFlagsInFile> 0)
				{
				 	# id read only remove option
				   if (!( -w $CurrentFilePath) )
				    {
				 		@com =`cmd /c attrib $CurrentFilePath -R`;
				 		chomp @com;
				 		push (@ReadOnlyFiles, "$1\n");		
			   	 	}
					print "Changed: $CurrentFilePath\n";
			  		open(SOURCE_FILE , "> $CurrentFilePath") || die "$0: Can't open $CurrentFilePath ";
		   	   		$NumOfFlags += $NumOfFlagsInFile;		
			  		#writing file back
		      		for $line ( @lineDB )
		      		{
		        		print SOURCE_FILE $line;
		      		}
		      		close SOURCE_FILE;
					$NumOfOpenFiles++;
				   	push (@OpenFiles, "$1\n");
				}
		  }
		}
#report statistic
		if ( $ReadOnlyFiles == 0 ) {
		    print "\n End of process :\n* $NumOfOpenFiles files were update\n";
		}
		else  {
			print "\n End of process :\n* $NumOfOpenFiles files were update\n";
			print "* $ReadOnlyFiles files were Read only\n";
		}
		print "\nFound flag $flag in path $path, $NumOfFlags times";
	}
}

print "\nDone Removing Flags\n";


############################################################################
# Functions		#08/16/2007 4:52PM
############################################################################
#start the handling when the first if with the flag found
sub StartHandlingIf ($@)
{
	my ($log_exp,@expressions) = @_;
	my ($ret,$str);
	#check key found
	# evaluate the logical expression according to the question
		if ($current_key eq 'if')
		{
			($ret,$str) = EvaluateExpressionArray(@expressions);
		}
		elsif ($current_key eq 'ifdef')
	  	{
	  	   	($ret,$str) = EvaluateIfdef(@expressions);
	   	}
		elsif ($current_key eq 'ifndef')
		{
			($ret,$str) = EvaluateIfndef(@expressions);
		}
	 $NumOfRemoval++;
	 $NumOfFlagsInFile++;
	 #if doesn't have an answer return new question
	 if ( $ret == -1 ) {
		my $temp = "\#$current_key $str";
		$current_key = '';
		return $temp;
	 }
	 # count number of opening if's
	 $StartCounter ++;
	 #remove this line
	 $remove_line = 1;
	 # check if need to remove lines under the flag
	 if ( $ret != 0 ) {
		$remove_code = 0;
	 }
	 else
	 {
	 	$remove_code = 1;
	 }
	 return '';      
}

#start the handling when the first elif with the flag found
sub StartHandlingElif ($@)
{
	my ($log_exp,@expressions) = @_;
	#check key found
	my ($ret,$str);
	#evaluate the expression
	($ret,$str) = EvaluateExpressionArray(@expressions);
	$NumOfRemoval++;
	$NumOfFlagsInFile++;
	#if doesn't have an answer return new question
  	 if ( $ret == -1 ) {
		my $temp = "\#$current_key $str";
		$current_key = '';
		return $temp;
	 }
	 # count number of opening if's
	 $StartCounter ++;
	 #if the answer is true convert elif to else and force remove afte exiting it
	 if ( $ret != 0 ) {
		my $temp = "\#else";
		$remove_line = 0;
		$remove_code = 0;
		$force_remove = 1;
		return $temp;
  	 }
	 else
	 {
		#answer is false - remove the code
		$remove_line = 1;
		$remove_code = 1;
		$force_remove = 0;
		return '';
	 }  
}

#evaluate definition of a variable name
sub EvaluateIsDefined ($)
{
	my $str = shift;
	if ( $str eq $flag ) {
		#check if the flag exist and defined
		if ( exists $flagdefinitions{$str} && ( defined $flagdefinitions{$str} )) {
				return ($flagdefinitions{$str},'');
		}
		return (0,'');
	}
	elsif ( (exists $flagdefinitions{$str}) && (defined $flagdefinitions{$str}) ) {
	   		return ($flagdefinitions{$str},$str);
   	}
	elsif ($str =~ /^\d+$/)
	{
		return ($str,$str);
	}
	#if unknown flag return -1
	return (-1,$str);
}


#evaluate an arithmetic expression
sub EvaluateArithmeticExpression ($)
{
	my $str = shift;
	#check id it conatins the flag
	if ( $str =~ /$flag/ ) {
		#contain flag
		my ($first,$op,$second) = split(/(\=\=|\<\=|\!\=|\>\=|\<|\>)/, $str);
		#if no operator check definition
		if ( $op eq '' ) {
			return EvaluateIsDefined($str);
		}
		#evaluate each side
		my ($e1,$rstr1) = EvaluateIsDefined($first);
		my ($e2,$rstr2) = EvaluateIsDefined($second);
		my $one = (($e1==-1)?0:$e1);
		my $two = (($e2==-1)?0:$e2);
		my $ret = eval($one.$op.$two);
		return ($ret,'');
	}
	#doent contain flag
	return EvaluateIsDefined($str);
}

#evaluates a logical expression
sub EvaluateLogicalExpression ($$$$$)
{
	my $ret1 = shift;
	my $str1 = shift;
	my $op = shift;
	my $ret2 = shift;
	my $str2 = shift;
	my $ret;
	#if one of the truth values is undefined try to evaluate
	if ( ($ret1 == -1) || ($ret2 == -1) ) {
		if ( ($op eq '||' ) && (($ret1 > 0) || ($ret2 > 0))) {
			$ret = 1;
		}
		elsif ( ($op eq '&&' ) && (($ret1 == 0) || ($ret2 == 0))) {
			$ret = 0;
		}
		else
		{
			#if cant eval return -1
			$ret = -1;
		}
	}
	else
	{
		#evaluate
		$ret = eval($ret1.$op.$ret2);
	}
	#if we have a value return it
	if ( $ret != -1 ) {
		return($ret,'');
	}
	#check if 1 of the strings doesnt exist
	if ( $str2 eq '' ) {
		return ($ret,$str1);
	}
	elsif ($str1 eq '') {
		return ($ret,$str2);
	}
	#return 1 op 2
	return ($ret,$str1.$op.$str2);
}

#evaluate ifdef
sub EvaluateIfdef (@)
{
	my @expr = @_;
	my ($ret,$rstr) = EvaluateIsDefined($expr[0]);
	$ret = 1 if ($ret >0);
	return ($ret,$rstr);
}

#evaluate ifndef
sub EvaluateIfndef (@)
{
	my @expr = @_;
	my ($e,$rstr) = EvaluateIsDefined($expr[0]);
	my $temp = ( ($e == -1) ? ($e) : ( ($e != 0) ? 0 : 1 ));
	return ($temp,$rstr);
}

#checks the nuber of open close brackets
sub HasWrapingBrackets ($)
{
	my $str = shift;
	my $open=0;
	my $close=0;
	my $temp = $str;
	while ( length($temp) > 0 ) {
		my $temp2 = substr($temp,0,1,'');
		$open++ if ($temp2 eq '(' );
		$close++ if ($temp2 eq ')' );
		#found the middle
		if ( ($open == $close) && ($open > 0) && (length($temp) > 0) ) {
			return 0;
		}
	}
	if ( $open == $close ) {
		if ( $open == 0 ) {
			return 3;
		}
		else
		{
		   	return 1;
		}
	}
	else
	{
		return 2;
	}
	return 1;
}

#evaluate a complex expression recursively
sub EvaluateExpressionArray (@)
{
	my @expr = @_;
	my $size = scalar(@expr);
	return 0 if (!($size));
	my $str = join ('',@expr);
	my @ex;
	my $open=0 ;
	my $close=0;
	my $found=0;
	my $temp = $str;
	my $first;
	my $second;
	my $op;
	#print "eval expression: @expr\n";
	#seperate the middle logical expression according to the brackets
	while ( length($temp) > 0 ) {
		my $temp2 = substr($temp,0,1,'');
		$first .= $temp2;
		$open++ if ($temp2 eq '(' );
		$close++ if ($temp2 eq ')' );
		#found the middle
		if ( ($open == $close) && ($open > 0) && (length($temp) > 0) ) {
			$found = 1;
			if ( (substr($temp,0,1) eq substr($temp,1,1)) || ((substr($temp,0,1) ne '|') && (substr($temp,0,1) ne '&') ) ) {
				#2 char operand
				$second = substr($temp,2);
				$op = substr($temp,0,2);
			}
			else
			{
				#1 char op
				$second = substr($temp,1);
				$op = substr($temp,0,1);
			}

			#handle & precedence
			if ( ($op eq '&&') && (index($second,'||') != -1 ) && (HasWrapingBrackets($second) == 0) ) {
				$first .= $op;
				$op = '';
				$temp = $second;
				$found = 0;
				$open = 0;
				$close = 0;
				next;
			}
			last;
	  	}
		#handle operator with no brackets
		if ( ($temp2 eq '|') || ($temp2 eq '&') ) {
			if ( substr($temp,0,1) eq $temp2 ) {
			   $temp2 .= substr($temp,0,1,'');
			}
			$op = $temp2;
			substr($first,(length($first)-1),1,'');
			$second = $temp;
			if ( (HasWrapingBrackets($first) == 3) || (HasWrapingBrackets($second) == 3) ) {
				$found =1;
				last;
			}
			$first .= $op;
			$op = '';
			$second = '';
		}
	}
	#handle not
	if ( (!($found)) && (substr($first,0,1) eq '!') ){
		#eval without the not
		my ($e,$rstr) = EvaluateExpressionArray(split('',substr($first,1)));
		#negate
		my $temp = ( ($e == -1) ? ($e) : ( ($e != 0) ? 0 : 1 ));
		if ( $rstr ) {
			return ($temp,"!$rstr");
		}
		else
		{
			return ($temp,'');
		}
	}
	#defined or redundant brackets
	if ((!($found)) && ($open >0 )) {
		if ( $first =~ /^defined/ ) {
			#handle defined
			$first =~ s/^defined//;
			my ($ret,$rstr);
			if ( substr($first,0,1) eq '(' ) {
				substr($first,0,1,'');
				substr($first,-1,1,'');
			}
			#eval definition
			($ret,$rstr) = EvaluateIsDefined($first);
			$ret = 1 if ($ret >0);
			if ( $rstr eq '' ) {
				return ($ret,'');
			}
			return ($ret,"defined($rstr)");
		}
		#remove parenthesys
		if ( ($expr[0] eq '(') && ($expr[-1] eq ')') ) {
			shift @expr;
			pop @expr;
		}
		else
		{
			die " \n **** Error: in file $CurrentFilePath , the line @expr doesnt have right parenthesys\n"
		 }
		#eval rec
		my ($ret,$rstr) = EvaluateExpressionArray(@expr);
		if ( $rstr eq '' ) {
			return ($ret,'');
		}
		return ($ret,"($rstr)");
   	}
	#define with no brackets
	if ((!($found)) && ($open == 0 ) && ($first =~ /^defined/)) {
			#handle defined
			$first =~ s/^defined//;
			my ($ret,$rstr);
			#eval definition
			($ret,$rstr) = EvaluateIsDefined($first);
			$ret = 1 if ($ret >0);
			if ( $rstr eq '' ) {
				return ($ret,'');
			}
			return ($ret,"defined($rstr)");
	}
	#opertion with operands in brackets
	if ( $found ) {
		#logical expression
		if ( $op =~ /[\|\&]/ ) {
			#eval operands
			my ($e1,$rstr1) = EvaluateExpressionArray(split('',$first));
			my ($e2,$rstr2) = EvaluateExpressionArray(split('',$second));
			#eval expression
			my ($ret,$rstr) = EvaluateLogicalExpression($e1,$rstr1,$op,$e2,$rstr2);
			return ($ret,$rstr);
		}
		else
		{
			#arithmetic expression
			#eval each side
			my ($e1,$rstr1) = EvaluateExpressionArray(split('',$first));
			my ($e2,$rstr2) = EvaluateExpressionArray(split('',$second));
		   	my $ret;
			if ( $str =~ /$flag/ ) {
				$e1 = (($e1==-1)?0:$e1);
	   	   		$e2 = (($e2==-1)?0:$e2);
		   		$ret = eval($e1.$op.$e2);
				return($ret,'') ;
			}
			if ( ($e1 == -1) || ($e2 == -1) ) {
				return (-1,$rstr1.$op.$rstr2);
			}
			$ret = eval($e1.$op.$e2);
			return ($ret,$rstr1.$op.$rstr2);
	   	}
	}
	else
	{
		#arithmetic expression or definition
		my ($ret,$rstr) = EvaluateArithmeticExpression($first);
		return ($ret,$rstr);
	}
}

#removes undefs from array
sub RemoveUndefsFromArray (@)
{
	my @arr,$temp;
	my @temparr;
	my $i = 0;
	for $temp (@_)
	{
		#print "$temp\n";
		if ( $temp ne undef ) {
			push(@arr,$temp);
		}
	}
	return @arr;
}

#seperate comment and data
sub RemoveComment ($)
{
    my $string = shift;
	my @arr = split(/(\/\/|\/\*)/,$string);
	$string =~ /(.*?)(\/\/|\/\*)(.*)/;
	#return ($arr[0],$arr[1].$arr[2]);
	if ( defined($arr[1]) ) {
		 return ($1,$2.$3);
	}
	else
	{
		if ( $string =~ /\*\/$/ ) {
			return('',$string);
		}
		return ($string,'');
	}

}


#the start handling a key with a flag switch
sub StartCheckKey($@)
{
		my ($data,@Exprs) = @_;
		#check key found
							#choose handling type
	  						if ($current_key eq 'if')
	  						{
							  	$data = StartHandlingIf($data,@Exprs);
	  						}
	  		   		   		elsif ($current_key eq 'elif')
	  						{
	  							$data = StartHandlingElif($data,@Exprs);
	  						}
	  		   				elsif ($current_key eq 'ifdef')
	  			   			{
	  							$data = StartHandlingIf($data,@Exprs);
	  		   				}
	  			   			elsif ($current_key eq 'ifndef')
	  		   				{
	  							$data = StartHandlingIf($data,@Exprs);
	  		   				}
	  						elsif ($current_key eq 'endif')
	  						{
	  						   	$data = "\#$current_key";
								$current_key = '';
	  						}
	  						elsif ($current_key eq 'else')
	  						{
								 $data = "\#$current_key";
								 $current_key = '';
	  						}
	   return $data;
}

#continue handling a key with a flag switch
sub ContinueCheckKey($$)
{
	my $data = shift;
	my $key = shift;
	#check key found
						#choose handling type
	  		  			if ($current_key eq 'if')
	  			   		{
	  				   		$data = ContinueHandlingIf($data,$key);
	  			   		}
	  		   	   		elsif ($current_key eq 'elif')
	  			   		{
	  			  	   		$data = ContinueHandlingElif($data,$key);
	  			   		}
	  		   	 		elsif ($current_key eq 'ifdef')
	  			 		{
	  			 			$data = ContinueHandlingIf($data,$key);
	  		   	 		}
	  			 		elsif ($current_key eq 'ifndef')
	  		   	 		{
	  			 		    $data = ContinueHandlingIf($data,$key);
	  		   	 		}
	  			 		elsif ($current_key eq 'endif')
	  			 		{
	  			 		   	print "\nerror in line number $line_num cont-endif";
      	   	 		   		die " \n **** Error: endif with flag $flag not in comment in file $CurrentFilePath"
	  			 		}
	  					elsif ($current_key eq 'else')
	  					{
	  			   		   	print "\nerror in line number $line_num cont-else";
      	   			 	  	die " \n **** Error: endif with flag $flag not in comment in file $CurrentFilePath"
	  					}
					return $data;
}

#checks if the file is in ignored list
sub IsIgonredFile($)
{
	my $name = shift;
	my $tmpfile;
	for $tmpfile ( @IgnoredFiles ) {
		return 1 if ($name =~ /$tmpfile$/);
	}
	return 0;
}

#checks if the file is in ignored folder list
sub IsIgonredFolder($)
{
	my $name = shift;
	my $tmpfile;
	for $tmpfile ( @IgnoredFolders ) {
		return 1 if ($name =~ /$tmpfile\\/);
	}
	return 0;
}

#handling new keys found when we are already inside an if\ifdef\ifndef region
sub ContinueHandlingIf($$)
{
	my $data = shift;
	my $key = shift;
	#check key found

   	  	if ($key eq 'elif')
   	  	{
			 #check that this is the elif related to this tag and we havent
			#alredy changed one elif
	   		if ( ($StartCounter == 1) && ($encountered_elif == 0) ) {
				if ( ($remove_code == 1) && ($force_remove == 0) ) {
					#the first elif is converted to if
					$data =~ s/$key/if/;
					$remove_line = 0;
	   		   		$remove_code = 0;
					$encountered_elif = 1;
					return $data;
			 	}
				else
				{
					#force removal
					$force_remove = 1;
					$remove_line = 1;
	   		   		$remove_code = 1;
					return '';
			   	}
			}
			return $data;
   	 	}
   	 	elsif ($key eq 'endif')
   	 	{
			#reset
			if ( $StartCounter == 0 ) {
			   	$remove_line = ($encountered_elif?0:1);
	   			$remove_code = 0;
				$force_remove = 0;
				$encountered_elif = 0;
				$current_key = '';
				return '' if ($remove_line);
			}
			return $data;
   	 	}
   		elsif ($key eq 'else')
   		{
			#switch deletion mode if not forced
			if ( ($StartCounter == 1) && ($encountered_elif == 0) ) {
				$remove_line = 1;
				if ( $force_remove == 0 ) {
					$remove_code = ($remove_code?0:1);
				}
	   			return '';
			}
		}
	return $data;
}

#handling new keys found when we are already inside an elif region
sub ContinueHandlingElif($$)
{
	my $data = shift;
	my $key = shift;
	#check key found
   	  	if ($key eq 'elif')
   	  	{
			#check that this is the elif related to this tag and we havent
			# alredy changed one elif
			if ( ($StartCounter == 1) && ($encountered_elif == 0) ) {
				#if the code above removed finish removing
				if ( ($remove_code == 1) && ($force_remove == 0) ) {
					$remove_line = 0;
	   		   		$remove_code = 0;
					$encountered_elif = 1;
					return $data;
			 	}
				else
				{
					#the code above remain - force removal on all code below
					$force_remove = 1;
					$remove_line = 1;
	   		   		$remove_code = 1;
					return '';
			   	}
			}
			return $data;
   	 	}
   	 	elsif ($key eq 'endif')
   	 	{
			#in case of endif - reset
			if ( $StartCounter == 0 ) {
				$remove_line = 0;
	   			$remove_code = 0;
				$force_remove = 0;
				$encountered_elif = 0;
				$current_key = '';
				return $data;
			}
			return $data;
   	 	}
   		elsif ($key eq 'else')
   		{
			#check that this is the else related to this tag and we havent
			#alredy changed one elif
		   	if ( ($StartCounter == 1) && ($encountered_elif == 0) ) {
				if ( ($remove_code == 1) && ($force_remove == 0) ) {
					#if the code above removed finish removing
					$remove_line = 0;
	   		   		$remove_code = 0;
					$encountered_elif = 1;
					return $data;
			 	}
				else
				{
					#the code above remain - force removal on all code below
					$force_remove = 1;
					$remove_line = 1;
	   		   		$remove_code = 1;
					return $data;
			   	}
			}
			return $data;
		}
	return $data;
}

#reads from the given file name the list under a given [string]
sub ReadParamsFromFile($$)
{
	my $name = shift;
	my $string = shift;
	my $line;
	my @array;
	my $inside_section = 0;
	open(SOURCE_FILE, "< $name") || die "\ncannot open file $name";
	#read file
	@file_lines = <SOURCE_FILE>;
	close SOURCE_FILE;
	#go over the lines
	foreach $line (@file_lines)
	{
		chomp $line;
		#[.*]doesn't count and end the section
		if ($line =~ /\[.*\]/)
		{
			$inside_section = 0;
		}
		#collect the items under the string
		if ($inside_section == 1)
		{
			#do not insert empty lines
			if ($line ne ""){
				push (@array,$line);
			}
		}
		#start collecting
		if ($line =~ /\[$string\]/)
		{
			$inside_section = 1;
		}	
	}
	return @array;
}

#reads from the given file name the list under a given [string]
sub ReadFlagsFromFile($$)
{
	my $name = shift;
	my $string = shift;
	my $line;
	my %hash;
	my $inside_section = 0;
	open(SOURCE_FILE, "< $name") || die "\ncannot open file $name";
	#read file
	@file_lines = <SOURCE_FILE>;
	close SOURCE_FILE;
	#go over the lines
	foreach $line (@file_lines)
	{
		chomp $line;
		#[.*]doesn't count and end the section
		if ($line =~ /\[.*\]/)
		{
			$inside_section = 0;
		}
		#collect the items under the string
		if ($inside_section == 1)
		{
			#do not insert empty lines
			if ($line ne ""){
				$line =~ /(\w+)\s*,\s*(\w+)/;
				$flag = $1;
				$val= $2;
				#numeric definition
				if ($val =~ /^\d+$/)
				{
					$hash{$flag}=$val;
				}
				#undefined
				elsif ($val eq 'undef')
				{
					$hash{$flag}=undef;
				}
				#another flag
				elsif (exists $hash{$val})
				{
						$hash{$flag}=$hash{$val}; 
				}
				else
				{
					die "Unknown value (=$val) for flag=$flag\n";
				}
			}
		}
		#start collecting
		if ($line =~ /\[$string\]/)
		{
			$inside_section = 1;
		}	
	}
	return %hash;
}


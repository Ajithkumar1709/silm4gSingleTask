#!/bin/sh
rm -r -f upsdefs.00*
sed 's:-I\\:-Ix\:\\:g' upsdefs.sub > upsdefs.000
sed 's:\\:\/:g'        upsdefs.000 > upsdefs.001
sed 's:w\::'$WROOT':g' upsdefs.001 > upsdefs.002
sed 's:x\::'$XROOT':g' upsdefs.002 > upsdefs.003

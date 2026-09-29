## 介绍

开发环境：`Windows`

硬件环境: `L505C-3E`

## 环境搭建
开发环境搭建说明详见 [L505C硬件 Bringup](https://yuque.antfin.com/bot-team/bot/pl6nih "Bringup")


## 编译
1. 选项配置：
    >1. Adapter->Select Platform->l50x (空格选中 l50x)
    >2. Adapter->enable redefine symbl (空格取消选中)
    >3. Adapter->Components->MEM Configuration (空格取消选中,保存后退出)

2. 在 bot 目录下，执行
    ```
    .\build.bat l50x
    ```
3. 生成文件在 `bot\..\out` 和 `bot\..\release` 目录下

## 附录

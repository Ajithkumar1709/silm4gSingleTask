#define SPIHANDLE uint32_t

typedef enum
{
    SPI_DIRECT_POLLING = 0,
    SPI_DIRECT_IRQ,
    SPI_DMA_POLLING,
    SPI_DMA_IRQ,
} drvSpiTransferMode;

typedef enum
{
    SPI_DI_0 = 0,
    SPI_DI_1,
    SPI_DI_2,
} drvSpiInputSel;

typedef enum
{
    SPI_CPHA_1Edge,
    SPI_CPHA_2Edge,
} drvSpiCphaPol;
#ifndef _NL_API_SPI_H_
#define _NL_API_SPI_H_


typedef enum
{
    SPI_CPOL_LOW = 0,
    SPI_CPOL_HIGH,
} drvSpiCpolPol;

typedef struct
{
    bool inputEn;
    uint8_t oe_delay;
    uint32_t name;
    uint32_t framesize;
    uint32_t baud;
    drvSpiCsPol cs_polarity0;
    drvSpiCsPol cs_polarity1;
    drvSpiCpolPol cpol;
    drvSpiCphaPol cpha;
    drvSpiInputSel input_sel;
    drvSpiTransferMode transmode;
    bool gpio_csEn;
    uint8_t gpio_pinId;
    drvSpiCsPol gpio_cs_polarity;
    bool gpio_cs_forceEN;
} drvSpiConfig_t;

typedef enum
{
    SPI_I2C_CS0 = 0,
    SPI_I2C_CS1,
    SPI_I2C_CS2,
    SPI_I2C_CS3,
    SPI_GPIO_CS,
} drvSpiCsSel;

typedef enum
{
    SPI_CS_ACTIVE_HIGH,
    SPI_CS_ACTIVE_LOW,
} drvSpiCsPol;

typedef struct
{
    uint32_t bits_per_word;
    uint32_t speed_hz;
    drvSpiCsSel cs;
    drvSpiCsPol cs_polarity;
}SPI_IOC;

typedef enum
{
    SPI_CLK_CTRL,
    SPI_DO_CTRL,
    SPI_CS0_CTRL,
    SPI_CS1_CTRL,
    SPI_CS2_CTRL,
#ifdef CONFIG_NL_BASE
		SPI_GPIO_CS_CTRL,
#endif
} drvSpiPinCtrl;

typedef enum
{
    SPI_CTRL,
    INPUT_CTRL,
    FORCE_0_CTRL,
    FROCE_1_CTRL,
} drvSpiPinState;

/**
 * @brief    spi初始化时，需要调用。同一个控制器不能重复调用
 *
 * @param <cfg>入参，spi配置项，用于初始化spi
 * @param <spiFd>出参，open成功后，返回的句柄
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_spi_open(drvSpiConfig_t cfg, SPIHANDLE * spiFd);

/**
 * @brief    spi去初始化，spi不再使用时，调用该函数释放spi
 *
 * @param <spiFd>入参，为open成功后返回的句柄，close时需要关闭句柄
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_spi_close(SPIHANDLE * spiFd);

/**
 * @brief    用于spi数据发送
 *
 * @param <spiFd>open操作时返回的句柄；
 * @param <spiIoc>设置此次数据发送使用的位宽、速率、片选及片选极性；
 * @param <sendaddr>发送的数据缓冲区；
 * @param <size>缓冲区的大小，与位宽有关；
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_spi_send(SPIHANDLE spiFd, SPI_IOC spiIoc, void * sendaddr, uint32_t size);

/**
 * @brief    sendaddr和readaddr的空间大小都为size，且都不为空。此函数既可以发送+接收，也可以单独接收
 *
 * @param <spiFd>open操作时返回的句柄；
 * @param <spiIoc>设置此次数据收发使用的位宽、速率、片选及片选极性；
 * @param <sendaddr>发送的数据缓冲区；
 * @param <readaddr>接收的数据缓冲区；
 * @param <size>缓冲区的大小，与位宽有关；
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_spi_recv(SPIHANDLE spiFd, SPI_IOC spiIoc, void * sendaddr, void * readaddr, uint32_t size);

/**
 * @brief    用来强制控制SPI的管脚状态，强制拉高，强制拉低，输入，或者恢复SPI来控制。
 *
 * @param <spiFd>open操作时返回的句柄；
 * @param <pinctrl>需要控制的spi引脚：0：spi_clk  1：spi_do  2：spi_cs0  3：spi_cs1  4：spi_cs2  5：spi_gpio_cs
 * @param <pinstate>强制控制的引脚状态：0：spi_ctrl  1：input_ctrl  2：force_0_ctrl  3：force_1_ctrl
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_spi_pinctrl(SPIHANDLE spiFd, drvSpiPinCtrl pinctrl, drvSpiPinState pinstate);

#endif
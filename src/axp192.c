/**
 * @file axp192.c
 * @brief Component to work with AXP192
 *
 * (C) 2020 - Timothee Cruse <timothee.cruse@gmail.com>
 * This code is licensed under the MIT License.
 */

#include "axp192.h"

#include "common_io_helpers.h"

#define LIBRARY_LOG_LEVEL IOT_LOG_INFO
#define LIBRARY_LOG_NAME  "axp192"
#include "iot_logging_setup.h"

/*-----------------------------------------------------------*/

static IotI2CHandle_t prvAXP192I2CHandle = NULL;

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

axp192_err_t eAXP192Init( axp192_config_t config )
{
    uint8_t i;
    prvAXP192I2CHandle = config.i2c_handle;

    IotLogDebug( "eAXP192Init: Setting up %u registers:", config.nb_init_regs );

    for ( i = 0; i < config.nb_init_regs * 2; i += 2 )
    {
        if ( eWriteI2CBytes( config.i2c_handle, AXP192_I2C_ADDRESS, config.init_regs + i, 2 ) != COMMON_IO_SUCCESS )
        {
            IotLogError( "eAXP192Init: Error writing %#04x @  %#04x", config.init_regs + i, config.init_regs + i + 1 );
            return AXP192_FAIL;
        }
        IotLogDebug( "eAXP192Init: Wrote %#04x @  %#04x", config.init_regs[ i ] , config.init_regs[ i + 1 ] );
    }

    return AXP192_SUCCESS;
}

/*-----------------------------------------------------------*/



/*-----------------------------------------------------------*/



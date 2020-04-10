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

axp192_err_t eAXP192SetRegisterBits(uint8_t register_address, uint8_t bits_to_set)
{
    uint8_t register_content[ 2 ] = { register_address, 0 };

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, register_content, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192SetRegisterBits: Failed to read 1 byte @ %#04x", register_address );
        return AXP192_FAIL;
    }
    IotLogDebug( "eAXP192SetRegisterBits: Read %#04x @ %#04x", register_content[ 0 ], register_address );

    register_content[ 1 ] = register_content[ 0 ] | bits_to_set;
    register_content[ 0 ] = register_address;
    if ( eWriteI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, register_content, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192SetRegisterBits: Error writing %#04x @  %#04x", register_content[ 1 ], register_address );
        return AXP192_FAIL;
    }
    IotLogDebug( "eAXP192SetRegisterBits: Wrote %#04x @ %#04x", register_content[ 1 ], register_address );

    return AXP192_SUCCESS;
}

/*-----------------------------------------------------------*/

axp192_err_t eAXP192ClearRegisterBits(uint8_t register_address, uint8_t bits_to_clear)
{
    uint8_t register_content[ 2 ] = { register_address, 0 };

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, register_content, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192ClearRegisterBits: Failed to read 1 byte @ %#04x", register_address );
        return AXP192_FAIL;
    }

    register_content[ 1 ] = register_content[ 0 ] & ~bits_to_clear;
    register_content[ 0 ] = register_address;

    if ( eWriteI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, register_content, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192ClearRegisterBits: Error writing %#04x @  %#04x", register_content[ 1 ], register_address );
        return AXP192_FAIL;
    }

    return AXP192_SUCCESS;
}

/*-----------------------------------------------------------*/

axp192_err_t eAXP192GetVbat( uint16_t * vbat )
{
    uint8_t read1 = 0x78, read2 = 0x79;

    *vbat = 0;

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, &read1, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVbat: Failed to read 1 byte @ %#04x", 0x78 );
        return AXP192_FAIL;
    }

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, &read2, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVbat: Failed to read 1 byte @ %#04x", 0x79 );
        return AXP192_FAIL;
    }

    *vbat = ( read1 << 4 ) + read2 ; // V

    IotLogDebug("eAXP192GetPowerVbat: VBat: %u", *vbat);

    return AXP192_SUCCESS;
}

axp192_err_t eAXP192GetVaps( uint16_t * vaps )
{
    uint8_t read1 = 0x7E, read2 = 0x7F;

    *vaps = 0;

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, &read1, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVaps: Failed to read 1 byte @ %#04x", 0x7E );
        return AXP192_FAIL;
    }

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, &read2, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVaps: Failed to read 1 byte @ %#04x", 0x7F );
        return AXP192_FAIL;
    }

    *vaps = ( read1 << 4 ) + read2; // V

    IotLogDebug("eAXP192GetPowerVaps: Vaps: %u", *vaps);

    return AXP192_SUCCESS;
}

axp192_err_t eAXP192SetSleep( void )
{
    uint8_t read1[ 2 ] = { AXP192_REG_VOFF_SHUTDOWN_VOLTAGE_SETTING, 0 };

    if ( eReadI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, read1, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVaps: Failed to read 1 byte @ %#04x", AXP192_REG_VOFF_SHUTDOWN_VOLTAGE_SETTING );
        return AXP192_FAIL;
    }

    read1[ 1 ] = ( 1 << 3 ) | read1[ 0 ];
    read1[ 0 ] = AXP192_REG_VOFF_SHUTDOWN_VOLTAGE_SETTING;

    if ( eWriteI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, read1, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVaps: Failed to write %#04x @ %#04x", read1[ 1 ], AXP192_REG_VOFF_SHUTDOWN_VOLTAGE_SETTING );
        return AXP192_FAIL;
    }

    read1[ 0 ] = AXP192_REG_DCDC1_DCDC3_LDO2_LDO3_SWITCH_CONTROL;
    read1[ 1 ] = 0x01;
    if ( eWriteI2CBytes( prvAXP192I2CHandle, AXP192_I2C_ADDRESS, read1, 1 ) != COMMON_IO_SUCCESS )
    {
        IotLogError( "eAXP192GetPowerVaps: Failed to write %#04x @ %#04x", read1[ 1 ], AXP192_REG_DCDC1_DCDC3_LDO2_LDO3_SWITCH_CONTROL );
        return AXP192_FAIL;
    }

    return AXP192_SUCCESS;
}

/*-----------------------------------------------------------*/



//******************************************************************************
//! @file $RCSfile: flash_api_lib.c,v $
//!
//! Copyright (c) 2007 Atmel.
//!
//! Use of this program is subject to Atmel's End User License Agreement.
//! Please read file license.txt for copyright notice.
//!
//! @brief This file contains the library of functions of:
//!             - Flash API (code in "Boot Flash Section")
//!             - for AT90CAN128/64/32.
//!
//! This file can be parsed by Doxygen for automatic documentation generation.
//! This file has been validated with AVRStudio-413528/WinAVR-20070122.
//!
//! @version $Revision: 3.20 $ $Name: jtellier $
//!
//! @todo
//! @bug
//******************************************************************************

//_____ I N C L U D E S ________________________________________________________
#include "../../../AtmelLib/lib_mcu/flash/flash_api_lib.h"

#include "../../../AtmelLib/lib_mcu/flash/flash_boot_lib.h"
#include "config.h"


//_____ D E F I N I T I O N S __________________________________________________

//_____ F U N C T I O N S ______________________________________________________

//------------------------------------------------------------------------------
//  @fn flash_api_wr_block
//!
//! This function calls flash_wr_block() function.
//!
//! @warning: The 64K page setting must be done before (ex: setting
//!           or clearing the RAMPZ register).
//! @warning: See flash_wr_block() function.
//!
//! @param: - src      Source of (SRAM) buffer Address.
//!         - dest     Destination, start address in Flash memory where data
//!                    must be written.
//!         - byte_nb  Number of byte to write.
//!
//! @return none
//!
//------------------------------------------------------------------------------
void flash_api_wr_block(U8* src, U16 dest, U16 byte_nb)
{
    flash_wr_block(src, dest, byte_nb);
}

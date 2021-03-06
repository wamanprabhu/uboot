/******************************************************************************
 *
 *  (C)Copyright 2006 - 2012 Marvell. All Rights Reserved.
 *
 *  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF MARVELL.
 *  The copyright notice above does not evidence any actual or intended
 *  publication of such source code.
 *  This Module contains Proprietary Information of Marvell and should be
 *  treated as Confidential.
 *  The information in this file is provided for the exclusive use of the
 *  licensees of Marvell.
 *  Such users have the right to use, modify, and incorporate this code into
 *  products for purposes authorized by the license agreement provided they
 *  include this notice and the associated copyright notice with any such
 *  product.
 *  The information in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/
 /********************************************************************************
Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	* Redistributions of source code must retain the above copyright notice,
	  this list of conditions and the following disclaimer.

	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.

	* Neither the name of Marvell nor the names of its contributors may be
	  used to endorse or promote products derived from this software without
	  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/
#include "WtpException.h"
#include "WtpDownloadApp.h"
//#include "FlashCodes.h"
#include "Tim.h"
#include "Port.h"
#include <sstream>

CWtpException::CWtpException(void)
{

	this->stringArgs = string("");
	this->intArgs = 0;
}
CWtpException::CWtpException(errorList ErrorNumber)
{
	this->ErrorNumber = ErrorNumber;
}
CWtpException::CWtpException(errorList ErrorNumber,int intArgs, string stringArgs)
{
	this->ErrorNumber = ErrorNumber;
	this->intArgs = intArgs;
	this->stringArgs = stringArgs;
}

CWtpException::~CWtpException(void){}

void CWtpException::setErrorNumber(int ErrorNumber)
{
	this->ErrorNumber = ErrorNumber;
}
void CWtpException::setIntArgs(int intArgs)
{
	this->intArgs = intArgs;
}
void CWtpException::setStringArgs(string& stringArgs)
{
	this->stringArgs = stringArgs;
}

int CWtpException::getErrorNumber()
{
	return this->ErrorNumber;
}
int CWtpException::getIntArgs()
{
	return this->intArgs;
}
string& CWtpException::getStringArgs()
{
	return this->stringArgs;
}

/**
* Method:	printError
* Input:	N/A
* Output:	void
* Desc:		Constructs and prints error messages corresponding to ErrorCode
*			specified in CWtpException object.
*/
void CWtpException::printError()
{
	stringstream ErrorMessage;
	CMisc misc;
	stringstream ssError;
	unsigned int errNo;

	ErrorMessage.str("");
	ErrorMessage << endl;
	switch(ErrorNumber)
	{

		case COMMANDLINE_PARSE_ERROR:
			return;
		case INVALID_COMMANDLINE_COMBINATION:
			ErrorMessage << " Error: Some of commandline options provided are not compatible with each other! " << endl;
			ErrorMessage << stringArgs << endl;
			break;
		case INVALID_TIM_FILE:
			ErrorMessage <<  " Error: Invalid TIM file supplied! Correct ID: 0x" << hex << TIMIDENTIFIER << "  Provided ID: 0x" << hex << intArgs;
			break;
		case OPENLOGFILE:
			ErrorMessage <<  " Error: Failed to open log file: WtptpLog.txt.";
			break;
		case NOT_ENUF_FILES:
			ErrorMessage <<  " Error: An image file with ID# "+stringArgs +" was not supplied by user!";
			break;
		case NO_MIN_ARGS:
			misc.PrintUsage();
			ErrorMessage <<  " Error: Minimum number of arguments not provided";
			break;
		case NO_TIMIMAGE:
			ErrorMessage <<  " Error: A Tim image file was not supplied! Exiting program.";
			break;
		case ZEROFILESDOWNLOAD:
			ErrorMessage <<  " Error: Did not supply any files for download!";
			break;
		case NO_PARTITION_TABLE:
			ErrorMessage <<  " Error: Don't have a PartitionTable image asked for by target";
			break;
		case NO_IMAGE:
			ErrorMessage <<  " Error: Don't have image type asked for by target" << stringArgs;
			break;
		case ABORTED_DOWNLOAD_FILE:
			ErrorMessage <<  " Error: Download file has aborted! :" << stringArgs;
			break;
		case FILE_OPEN_FAIL:
			ErrorMessage <<  " Error: fopen failed to open " << stringArgs << " file ";
			break;
		case INSUFFICIENT_BYTES_READ:
			ErrorMessage <<  " Error: fread only read " << intArgs << stringArgs ;
			break;
		case ABORTED_MASTERBLOCKHEADER:
			ErrorMessage <<  " Error: Download FBF MasterBlockHeader has aborted!";
			break;
		case READ_MASTERBLOCKHEADER:
			ErrorMessage <<	 " Error: Error reading Master Block Header from " << stringArgs  ;
				break;
		case READ_DEVICEHEADERS:
			ErrorMessage <<  " Error: Error reading Device Headers from " << stringArgs  ;
			break;
		case UNKNOWN_DEVICENUMBER:
			ErrorMessage <<  " Error: Unknown Device Number - DeviceNum: " << stringArgs;
			break;
		case UNKNOWN_IMAGENUMBER:
			ErrorMessage <<  " Error: Unknown Image Number - ImageNum: " << stringArgs;
			break;
		case NO_KEYFILE:
			ErrorMessage <<  " Error: Did not supply KEY file for JTAG re-enablement!";
			break;
		case READ_KEYFILE:
			ErrorMessage <<  " Error: ReadKeyFile failed while processing file " << stringArgs;
			break;
		case INVALID_COMMANDLINE_OPTION:
			ErrorMessage <<  " Error: Command line option " << stringArgs << " is invalid!";
			break;
		case INVALID_PORTTYPE:
			ErrorMessage <<  " Error: Port Type parameter is required and must be USB or UART.";
			break;
		case INVALID_MESSAGEMODE:
			ErrorMessage <<  " Error: Message mode parameter value not recognized.";
			break;
		case PORTTYPE_WITH_MESSAGE_ONLY:
			ErrorMessage << " Error: Can only select port type " << endl << " option with Message Mode!";
			break;
		case NO_FEATURE_IN_DISABLED_MSG_MODE:
			ErrorMessage << " Error: Cannot do image downloads, JTAG reenablement or Uploads in DISABLED Message Mode";
			break;
		case INVALID_DECLARATION_STATEMENT:
			ErrorMessage << " Error: " << stringArgs << " declaration statement is invalid!" << endl<<" Format:" << stringArgs <<" = filename ";
			break;
		case UPLOAD:
			ErrorMessage << " Error: Upload Failed!" << stringArgs;
			break;

		case RSAKEYLENGTH:
			ErrorMessage << " Error:Reading RSA KeyLength from file" ;
			break;
		case RSAFLASHTYPE:
			ErrorMessage << " Error:Reading flash type from file";
			break;
		case RSAISSUEDATE:
			ErrorMessage << " Error:Reading Issue Date from file" ;
			break;
		case RSAOEMUNIQUEID:
			ErrorMessage << " Error:Reading OEM Unique ID from file" ;
			break;
		case RSAHASHVALUELENGTH:
			ErrorMessage << " Error:Reading Hash value length from file" ;
			break;
		case RSAEXPONENT:
			ErrorMessage << " Error:Reading RSA Exponent from file" ;
			break;
		case RSAPRIVATEKEY:
			ErrorMessage << " Error:Reading RSA Private Key from file";
			break;
		case RSAPUBLICKEY:
			ErrorMessage << " Error: Reading RSA Public Key from file";
			break;
		case RSAMODULUS:
			ErrorMessage << " Error:Reading RSA Modulus from file ";
			break;
		case IPPSRSAGETSIZE:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsRSAGetSize:(" << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSRSAINIT:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsRSAInit:(" << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSBIGNUMGETSIZE:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsBigNumGetSize:( " << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSBIGNUMINIT:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsBigNumInit:( " << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSRSASETKEY:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsRSASetKey:("<< stringArgs <<") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSRSAENCRYPT:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsRSAEncrypt:(" << stringArgs << ") has failed!ErrorCode:" << dec << (int)errNo;
			break;
		case IPPSGET_BN:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsGet_BN:(" << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;
			break;
		case IPPSSET_BN:
			ssError << hex << intArgs;
			ssError >> errNo;
			ErrorMessage << " Error: EncryptSignature ippsSet_BN:(" << stringArgs << ") has failed!ErrorCode:"  << dec << (int)errNo;;
			break;
		case SETUPDIGETCLASSDEVS:
			ErrorMessage << " Error: SetupDiGetClassDevs failed with error " << intArgs;
			break;
		case SETUPDIENUMDEVICEINTERFACES:
			ErrorMessage << " Error: SetupDiEnumDeviceInterfaces failed with error " << intArgs;
			break;
		case MEM_ALLOC_PSP_DEVICE_INTERFACE_DETAIL_DATA:
			ErrorMessage << " Error: Failed to allocate memory for PSP_DEVICE_INTERFACE_DETAIL_DATA.";
			break;
		case SETUPDIDEVICEINTERFACEDETAIL:
			ErrorMessage << " Error: SetupDiGetDeviceInterfaceDetail failed with error " << intArgs;
			break;
		case OPENUSBPORT:
			ErrorMessage << " Error: OpenUsbPort failed! ";
			if(!stringArgs.empty())
				ErrorMessage << stringArgs;
			break;
		case READUSBPORT:
			ErrorMessage<< "Read USB Port failed!" ;
			if(intArgs != 0)
				ErrorMessage << "Error Number:" << intArgs;
			break;
		case WRITEUSBPORT:
			ErrorMessage<< "Write USB Port failed!" ;
			if(intArgs != 0)
				ErrorMessage << "Error Number:" << intArgs;
			if(!stringArgs.empty())
				ErrorMessage << stringArgs;
			break;
		case OPENUARTPORT:
			ErrorMessage << " Error: OpenUartPort failed!" ;
			if(intArgs != 0)
			ErrorMessage << "Error Number:" << intArgs << ". ";
			ErrorMessage << "Device Name : " << stringArgs;
			break;
		case READUARTPORT:
			ErrorMessage<< "Read UART Port failed!" ;
			if(intArgs != 0)
				ErrorMessage << "Error Number:" << intArgs;
			break;
		case WRITEUARTPORT:
			ErrorMessage<< "Write UART Port failed!" ;
			if(intArgs != 0)
				ErrorMessage << "Error Number:" << intArgs;
			break;
		case GETCOMMSTATE:
			ErrorMessage << " Error: GetCommState failed with error " << intArgs << ". Port: " << stringArgs;
			break;
		case GETCOMMCONFIG:
			ErrorMessage << " Error: GetCommConfig failed with error " << intArgs << ". Port: " << stringArgs;
			break;
		case SETCOMMSTATE:
			ErrorMessage << " Error: SetCommState failed with error " << intArgs << ". Port: " << stringArgs;
			break;
		case SETCOMMMASK:
			ErrorMessage << " Error: SetCommMask failed with error " << intArgs << ". Port: " << stringArgs;
			break;
		case SETUPCOMM:
			ErrorMessage << " Error: SetupComm failed with error " << intArgs << ". Port: " << stringArgs;
			break;
		case SETCOMMTIMEOUTS:
			ErrorMessage << " Error: SetCommTimeouts failed with error " << intArgs << " for " << stringArgs;
			break;
		case CLEARCOMMERROR:
			ErrorMessage << " Error: ClearCommError failed with error " << intArgs << ". Port: "<< stringArgs;
			break;
		case NACK_WTPCR:
			ErrorMessage << " Error: SendWtpCR returned a NACK!";
			break;
		case NACK_FORCEUART:
			ErrorMessage << " Error: Send Force UART Mode returned a NACK!";
			break;
		case NACK_FORCECONSOLE:
			ErrorMessage << " Error: Send Force Console Mode returned a NACK!";
			break;
		case NACK_PREAMBLE:
			ErrorMessage << " Error: SendPreamble returned a NACK!";
			break;
		case NACK_GETVERSION:
			ErrorMessage << " Error: GetVersion returned a NACK!";
			break;
		case NACK_SELECTIMAGE:
			ErrorMessage << " Error: SelectImage returned a NACK!";
			break;
		case NACK_VERIFYIMAGE:
			ErrorMessage << " Error: VerifyImage returned a NACK!";
			break;
		case NACK_DATAHEADER:
			ErrorMessage << " Error: DataHeader returned a NACK!";
			break;
		case NACK_DATA:
			ErrorMessage << " Error: Data returned a NACK!";
			break;
		case NACK_DONE:
			ErrorMessage << " Error: Done returned a NACK!";
			break;
		case NACK_DISCONNECT:
			ErrorMessage << " Error: Disconnect returned a NACK!";
			break;
		case PLATFORM_DISCONNECT:
			ErrorMessage << " Error: Target requested Disconnect!";
			break;
		case NACK_PUBLICKEY:
			ErrorMessage << " Error: PublicKey returned a NACK!";
			break;
		case NACK_PASSWORD:
			ErrorMessage << " Error: Password returned a NACK!";
			break;
		case NACK_SIGNEDPASSWORD:
			ErrorMessage << " Error: SignedPassword returned a NACK!";
			break;
		/*case NACK_OTPVIEW:
			ErrorMessage << " Error: OtpView returned a NACK!";
			break;
		case NACK_DEBUGBOOT:
			ErrorMessage << " Error: DebugBoot returned a NACK!";
			break;*/
		case NACK_GETPROTOCOLVERSION:
			ErrorMessage << " Error: GetProtocolVersion returned a NACK!";
			break;
		case NACK_GETPARAMETERS:
			ErrorMessage << " Error: GetParameters returned a NACK!";
			break;
		case NACK_UPLOADDATAHEADER:
			ErrorMessage << " Error: UploadDataHeader returned a NACK!";
			break;
		case NACK_UPLOADDATA:
			ErrorMessage << " Error: Upload data returned a NACK!";
			break;
		case JTAGENABLER_FAILED:
			ErrorMessage << " Error: JtagEnableOverMedia failed!" << stringArgs ;
			break;
		case CREATEPIPE:
			ErrorMessage << " Error: CreatePipe failed!";
			ErrorMessage << stringArgs;
			break;
		case SETHANDLEINFORMATION:
			ErrorMessage << " Error: SetHandleInformation failed!";
			ErrorMessage << stringArgs;
			break;
		case CREATEPROCESS:
			ErrorMessage << " Error: Create JtagEnabler process failed!";
			ErrorMessage << "Error Number:" << intArgs;
			break;
		case NOTSUPPORTED:
			ErrorMessage << "Feature not supported!" << stringArgs;
			break;
		default:
			ErrorMessage << "Unknown error";
	}
	ErrorMessage << endl;
	misc.UserMessagePrintStr(true,ErrorMessage.str());
}

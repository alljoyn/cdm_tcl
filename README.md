CDM Service Framework
=====================

Welcome to the CDM Service Framework.

CDM Service Framework provides easy methods to implement CDM controllee and controller applications.
CDM Service Framework is based on AJTCL v16.10.


Folder Structure
----------------
<pre>
cdm_tcl
+---inc
|   \---interfaces
|       +---environment
|       +---input
|       +---operation
|       \---userinterfacesettings
|
+---samples
|   +---certificates
|   +---DeviceEmulator
|   |   \---Models
|   |       +---environment
|   |       +---input
|   |       +---operation
|   |       \---userinterfacesettings
|   |
|   +---DeviceXML
|   +---LampDevice
|   +---TemperatureSensor
|   \---Utils
|
\---src
    +---CdmControllee
    +---interfaces
    |   +---environment
    |   +---input
    |   +---operation
    |   \---userinterfacesettings
    |
    \---utils

</pre>

##### cdm_tcl/inc Public headers for CDM TCL
 * interfaces: interface related header files
 * utils: utility related header files

##### cdm_tcl/samples Samples that demonstrate the features and use of CDM TCL
 * cdm_tcl/samples/certificates: certificate files used by the CdmSecurity utility
 * DeviceEmulator - Refer to Device Emulator section in this document
 * DeviceXML contains device xml files used by the device emulator
 * LampDevice is sample that uses the CDM utilities and implements an HSV model and a Switch model
    - The HSV model composes of the Brightness and the Color interfaces
    - The Switch model composes of the OnOffStatus, OnControl and OffControl interfaces
 * TemperatureSensor is a dual featured sample
    - It can be run as a virtual device on its own or through CDM OS (Refer to CDM STD CORE documentation)
    - It can be compiled and run on a Raspberry Pi 3 model b with the Sense Hat and become a real temperature sensor
 * All samples here are setup for CDM OS - Please see the CDM Std Core README for details

##### cdm_tcl/src The implementation of the CDM TCL framework and Interfaces
 * CdmControllee: The controllee framework
 * interfaces: CDM interface implementations
 * utils: The utility library contains utilities that wrap some boiler plate and make working with AllJoyn and CDM easier but it is not required
    - CdmAboutData can be given the devices about xml and the utility will use it to setup the PropertyStore
    - CdmSecurity is a utility that can manage keys/certificates and be used to enable security
    - CdmSystem is used to manage AllJoyn and the message loop


Building
--------
You can build CDM Service Framework using 'scons'.
Please refer to
<a name="AllJoyn build instructions" href="https:///allseenalliance.org/developers/develop/building">AllJoyn Build Instruction </a>
for more details on setting up your environment.

  * Folder structure
<pre>
root-source-dir
    +---core
    |   \---ajtcl
    \---services
        +---base_tcl
        +---cdm
        \---cdm_tcl
</pre>

  * Build
<pre>
cd root-source-dir/core/ajtcl
scons TARG=linux WS=off VARIANT={debug|release}

cd root-source-dir/services/base_tcl
scons TARG=linux WS=off VARIANT={debug|release}

cd root-source-dir/services/cdm_tcl
scons TARG=linux WS=off VARIANT={debug|release}
</pre>

  * Output
<pre>
cdm_tcl
+---build
\---dist
    +---bin
    |   +---certificates
    |   \---DeviceXML
    |   
    +---include
    \---lib
</pre>

    - dist/bin : DeviceEmulator, LampDevice, TemperatureSensor
    - dist/lib : libajtcl_cdm, libajtcl_cdm_interfaces
    - dist/inc : public header files

Doxygen
-------
  * Make manual
<pre>
cd root-source-dir/services/cdm_tcl/docs
doxygen Doxygen_html
</pre>

# NXP Application Code Hub

[<img src="https://mcuxpresso.nxp.com/static/icon/nxp-logo-color.svg" width="100"/>](https://www.nxp.com)

## How to develop an electric bicycle dashboard design on MCXN947

This demo is an example of dashboard for electric bicycle. This demo is based on LVGL 8.3.10 and GUI Guider 1.6.0-GA. This demo can be used by customers to evaluate GUI performance of MCXN947. Here, this demo uses MCXN947 as target MCU and uses internal flash to store image source and font source. This demo supports various GUI widgets to show customer information such as meter panel, chart, label.

#### Boards: FRDM-MCXN947

#### Categories: HMI

#### Peripherals: DISPLAY

#### Toolchains: MCUXpresso IDE

## Table of Contents

1. [Software](#step1)
2. [Hardware](#step2)
3. [Setup](#step3)
4. [Results](#step4)
5. [FAQs](#step5) 
6. [Support](#step6)
7. [Release Notes](#step7)

## 1. Software<a name="step1"></a>

The software for this demo is delivered in raw source files and MCUXpresso IDE projects. Software version:

1. Download [SDK_2_14_0_FRDM-MCXN947](https://mcuxpresso.nxp.com/en/welcome).

2. Download and install [MCUXpresso IDE V11.9.0 or later](https://www.nxp.com/design/design-center/software/development-software/mcuxpresso-software-and-tools-/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE).

3. MCUXpresso IDE V11.9.0 for Visual Studio Code: This example supports MCUXpresso IDE V11.9.0 for Visual Studio Code, for more information about how to use Visual Studio Code please refer [here](https://www.nxp.com/design/training/getting-started-with-mcuxpresso-for-visual-studio-code:TIP-GETTING-STARTED-WITH-MCUXPRESSO-FOR-VS-CODE).

## 2. Hardware<a name="step2"></a>

The hardware environment for this demo are listed here:

1. **FRDM-MCXN947** 

2. **LCD-PAR-S035**

3. **Type-C** USB cable

4. **Personal Computer**

## 3. Setup<a name="step3"></a>

### 3.1 Step 1(Hardware configuration)

1. Prepare FRDM-MCXN947, Type-C USB cable and LCD-PAR-S035.  
   <img src="image/MCXN947_EBike_Hardware.png" width="548" height = "458"></img>

2. Plug LCD-PAR-S035 into J8 like this.  
   <img src="image/LCD_PlugInFRDM.png" width="390" height = "520"></img>

3. Configure the LCD module interface to 16-bit 8080 by setting the mode switch (SW1) to **0-1-0**.  
   <img src="image/FRDM_MCXN947_E_Bike_LcdMode.jpg" width="400" height = "322"></img>

4. Connect J17(MCU-LINK) on FRDM-MCXN947 and PC with Type-C USB cable.  
   <img src="image/FRDM_Debugger.png" width="389" height = "357"></img>

### 3.2 Step 2(Software configuration)

1. Open MCUXpresso IDE, in the Quick Start Panel, choose **Import from Application Code Hub**.  
   <img src="image/import_project_1.png" width="456" height = "357"></img>

2. Enter the demo name in the search bar.  
   <img src="image/import_project_2.png" width="800" height = "425"></img>

3. Click **Copy GitHub link**, MCUXpresso IDE will automatically retrieve project attributes, then click **Next>**.  
   <img src="image/import_project_3.png" width="800" height = "181"></img>

4. Select **main** branch and then click **Next>**, Select the MCUXpresso project, click **Finish** button to complete import.  
   <img src="image/import_project_4.png" width="854" height = "549"></img>

5. Click **Build** to start compiling the project.  
   <img src="image/FRDM_MCXN947_E_Bike_Result.png" width="1439" height = "552"></img>

6. To download program into MCU, please press **GUI Flash Tool** icon in MCUXpresso IDE.  
   <img src="image/FRDM_MCXN947_E_Bike_Download.png" width="1037" height = "310"></img>

### 3.3 Step 3(Run)

   Press **SW1** button on **FRDM-MCXN947** board to run this demo.

## 4. Results<a name="step4"></a>

When this demo board is powered-up and then press reset **SW1** button, the demo will show the home screen. Then **switch the screens towards forward or backward by sliding right or left on the display**.  
  <img src="image/MCXN947_EBike_Screen_1.png" width="639" height = "203"></img>  
  <img src="image/MCXN947_EBike_Screen_2.png" width="628" height = "193"></img>  
  <img src="image/MCXN947_EBike_Screen_3.png" width="621" height = "197"></img>

## 5. FAQs<a name="step5"></a>

No FAQs have been identified for this project.

## 6. Support<a name="step6"></a>

#### Project Metadata

<!----- Boards ----->

[![Board badge](https://img.shields.io/badge/Board-FRDM&ndash;MCXN947-blue)](https://github.com/search?q=org%3Anxp-appcodehub+FRDM-MCXN947+in%3Areadme&type=Repositories)

<!----- Categories ----->

[![Category badge](https://img.shields.io/badge/Category-HMI-yellowgreen)](https://github.com/search?q=org%3Anxp-appcodehub+hmi+in%3Areadme&type=Repositories)

<!----- Peripherals ----->

[![Peripheral badge](https://img.shields.io/badge/Peripheral-DISPLAY-yellow)](https://github.com/search?q=org%3Anxp-appcodehub+display+in%3Areadme&type=Repositories)

<!----- Toolchains ----->

[![Toolchain badge](https://img.shields.io/badge/Toolchain-MCUXPRESSO%20IDE-orange)](https://github.com/search?q=org%3Anxp-appcodehub+mcux+in%3Areadme&type=Repositories)

Questions regarding the content/correctness of this example can be entered as Issues within this GitHub repository.

> **Warning**: For more general technical questions regarding NXP Microcontrollers and the difference in expected funcionality, enter your questions on the [NXP Community Forum](https://community.nxp.com/)

[![Follow us on Youtube](https://img.shields.io/badge/Youtube-Follow%20us%20on%20Youtube-red.svg)](https://www.youtube.com/@NXP_Semiconductors)
[![Follow us on LinkedIn](https://img.shields.io/badge/LinkedIn-Follow%20us%20on%20LinkedIn-blue.svg)](https://www.linkedin.com/company/nxp-semiconductors)
[![Follow us on Facebook](https://img.shields.io/badge/Facebook-Follow%20us%20on%20Facebook-blue.svg)](https://www.facebook.com/nxpsemi/)
[![Follow us on Twitter](https://img.shields.io/badge/Twitter-Follow%20us%20on%20Twitter-white.svg)](https://twitter.com/NXP)

## 7. Release Notes<a name="step7"></a>

| Version | Description / Update                    | Date                         |
|:-------:| --------------------------------------- | ----------------------------:|
| 1.0     | Initial release on Application Code Hub | January 30<sup>th</sup> 2024 |

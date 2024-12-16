# Prompt for creating a CloudCoin Client
## Overview: 

CloudCoins are files that contain a serial number and twenty five authenticity numbers. The authenticity numbers are GUIDs that act like passords. There a


# DEPOSIT 
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.
[Depoit Prep](#deposit-prep) | Checks folders for work from other jobs that were not completed
[Receipt Started](#receipt-starter) | Creates a GUID that will be used as the deposit ID. 
[File Picker](#file-picker) | Creates a list off all the files that will be deposited
[File Unpacker](#file-unpacker) | Unzip files, removes bin from PNGs and seperates multi-coin files into individual files. 
[Conflict Checker](#confilict-checker) | Makes sure that the coins being authenticated are not already in the file system. 
[GUID Generation](#guid-generation) | Creates the GUIDs that will be used to change ANs and writes them to file. 
[Timeout Calculator](#timeout-calculator) | Uses the Detection Log to calculate the appropriate 
[Detection](#detection) | Changes the ANs in the PANs
[Mop Up Detection](#mop-up-detection) | Runs detection again if Sum does not work. 
[Detection Logger](#detection-logger) | Records speeds and outcomes of detection process
[Grader](#grader) | Determines if a coin is counterfeit or not based on the response from the RAIDA. 
[Limbo Fixer](#limbo-fixer) | Repair coins that are in Limbo
[Fracture Fixer](#fracture-fixer) | Fixed coins that are fracked 
[Receipt Recorder](#receipt-recorder) 

# DOWNLOAD LOCKER COINS



The client will do the following tasks:


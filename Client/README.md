# Prompt for creating a CloudCoin Client
## Overview: 

CloudCoins are files that contain a serial number and twenty five authenticity numbers. The authenticity numbers are GUIDs that act like passords. There a


# DEPOSIT 
Takes coins and changes their Authenticity numbers to change ownership. 

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
[Detection Command Prep](#detection-commnad-prep) | Changes the ANs in the PANs
[TCP/IP Decider](#tcp/ip-decider) | Decides if the TCP or UDP protocol will be used. 
[Detection Command Encryption](#detection-command-encryption) | Changes the ANs in the PANs
[TCP Detection Requester](#tcp-detection-requester) | Sends requests to the RAIDA and Receives Responses
[UPD Detection Requester](#udp-detection-requester) | Sends requests to the RAIDA and Receives Responses
[UDP Response Receiver](#udp-response-receiver) | Sends requests to the RAIDA and Receives Responses
[Decrypter](#decrypter) | Sends requests to the RAIDA and Receives Responses
[Mop Up Detection](#mop-up-detection) | Runs detection again if Sum does not work. 
[Detection Logger](#detection-logger) | Records speeds and outcomes of detection process
[Grader](#grader) | Determines if a coin is counterfeit or not based on the response from the RAIDA. 
[Failed Pass Processor](#failed-pass-processor) | decides if a coin can be considered authentic and makes a plan. 
[Limbo Fixer](#limbo-fixer) | Repair coins that are in Limbo
[Fracture Fixer](#fracture-fixer) | Fixed coins that are fracked 
[Receipt Recorder](#receipt-recorder) 

# DOWNLOAD LOCKER COINS
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.
[PEEK](#echo) | Asks the RAIDA what the serial numbers are that are in the locker
[GET](#echo) | Tells RAIDA to change coins ANs. 

# MAKE CHANGE
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.

# JOIN COINS
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.

# CREATE LOCKER
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.
[PUT](#echo) | Put's coins into a locker

# COUNT COINS
Process | Purpose
---|---
[Count Coins](#count-coins) | Looks at all the coins in the Bank, Fracked, Limbo folders. 

# BACKUP COINS
Process | Purpose
---|---
[Backup](#echo) | Gathers files into zip files and saves them where directed. 


# SHOW RAIDA STATUS 
Process | Purpose
---|---
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.

# WITHDRAW COINS
Sees if coins need to be broke or join. Remove coins
Process | Purpose
---|---
[Withdraw](#withdraw) | removes coins


The client will do the following tasks:


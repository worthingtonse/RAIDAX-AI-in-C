# Prompt for creating a CloudCoin Client
## Overview: 

CloudCoins are files that contain a serial number and twenty five authenticity numbers. The authenticity numbers are GUIDs that act like passords. There a


# DEPOSIT 
Takes coins and changes their Authenticity numbers to change ownership. 

Process | Purpose
---|---
[Count Coins](#count-coins) | Tells you how many coins are in the wallets
[Echo](#echo) | Echos 25 servers while the user is choosing files to authenticate.
[Deposit Prep](#deposit-prep) | Checks folders for work from other jobs that were not completed
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

# Count Coins

<!--
The function begins by starting a timer. 

The function reads a file in the root folder called count.#.txt (where the hash symbol is an unknown number) into a string.  

The number in the file name is the amount of seconds it took to finish the last count. 

It examines the time stamp on the file. If the file was changed more than the number of seconds for last count, the string has the world "old" added to the end. Otherwise the string has the word "new" added to it. 

The function returns this string but then the function will continue to do work. 
-->
It counts how many coins are in the coin wallets by doing the following:

There is root folder called Coins. Within the Coins folder is a folder called Wallets. 

If there is no Wallet folder then the program must create it. 

Within the Wallets folder there will be a folder with the same name as the wallet name. 

If there are no folders in the Wallet folder, then a folder named "Default" should be created with the following subfolders:

```dos
Wallets
   └── Default
      ├── Bank
      ├── config.toml
      ├── Counterfeit
      ├── Export
      ├── Fracked
      ├── Import
      ├── Imported
      ├── Limbo
      ├── Receipts
      ├── Sent
      ├── Suspect
      ├── transactions.csv
      └── Trash
```

Within the wallet-name folders there are three folders name Bank, Fracked and Limbo. Within these three folders are coin files. The names of the coin files have many parts seperated with periods. The first part of the file is a  number that describes how many coins the file is worth. 

The number of coins in each of the three files should be totaled.

The function returns a JSON string that has an array of wallet names along with coin counts of each of the three folders. The following is an example of a Wallets folder with two sub folders named Default and Savings.  
```json
{
    "wallets": {
        "Default":
            {"bank": 1882,"fracked":9982.098, "limbo":88.000343, "1M":2,"100k":5,"10k":9,"1k";40,"100":15,"10":87,"1":83,"01":454   },
        "Savings": 
            {"bank": 34,"fracked":0.098, "limbo":18.267,"1M":2,"100k":5,"10k":9,"1k";40,"100":15,"10":87,"1":83,"01":454 }
    }
}
```
<!--
The timer is then stopped and the number of seconds is rounded up. 

The function then deletes the existing cound file in the root directory. 

A new count file is created with the number of seconds included in its name such as 
count.#.txt where the # is the number of seconds. 

This json is then written to a file count file. 
-->
The end. 

# Deposit
## File Unpacker

### Job Creator
Generate a GUID for receipt (or make the GUID do this or allow override)
Create a file in the receipts folder named the GUID and write start time to log. 

### Unzipper
unzipped checks import folder for zipped files. 
	If unzipped files already in imported check to see if they are identical
		same: Write over them. 
		different: give “already exists” tag (Log to receipt)
  
### Count Coins to Import
	Use file names to estimate number of coins that will be imported (report action log)

### PNG unpacker
Split the png file into single binary coins and keep those in the import folder.  
	If format is incorrect- Log and move to trash
 	If unpacked files already in imported check to see if they are identical
		same: Write over them. 
		different: give “already exists” tag. (Log to receipt)

### Binary unpacker
Read file, split up coins write them as TXT files with GUID name. 
	If format is incorrect- Log and move to trash

 ### Check Bank
 	See if coin is already in the Bank, Limbo or Fracked folder. 
  		Yes: Put into garbage. Note in receipt log. 
	If unpacked files already in imported check to see if they are identical
		same: Write over them. 
		different: give “already exists.random” tag. (Log to receipt)
  ### Generage GUIDs PANs
  	Generate GUIDs based on send type.
   
  ### Write TXT files to Suspect 
	Write them as TXT ini files with PANs. and write them to the Suspect folder.
	if the files are already in the suspect folder, see if they are identical. 
	identical files can be dropped.
	Non identical files re both given a random code and put into the Duplicates (Log issue)

### Move all files to the imported folder. 
	if the files are already in the suspect folder, see if they are identical. 
		identical files can be dropped.
		Non identical are given a random code and put into the ImportedDuplicates (Log issue)

## Authenticity Detector

### Create Requests
 	Create POWN Sum requests array. [TCP, raida, receipt number, request ]
  	Create POWN Sum Failed Request Array [raida, receipt number, request ]
   	Create POWN array
    	Create Failed POWN array.
     	Create Response Array
  
### POWN Sum
	Call pown sum. 
 	Write to file. 
### POWN one if necessary
	Call pown 
 	Write to file.

### Fix Limbo
	Create Fix Request Array. 
	Find service
### Fix Fracked
	Create array of Tickets
	Get Tickets by Sum
 	Get Ticket
  	Create Fix requests array
  	Fix
 
## Grade


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



Workflow to AI. 

Here is the workflow of date trough the datapipe. Please give me the rought ones of the program:

0. Prep
The Suspect folder is exampined. 
And if there are files there, the program will skip to pipeline #3 (Changeing the Passwords) and log "There are still unfinshed file from before"

1.Validating the Import folder.
The program looks into a folder called "Import".
If there are no files in the Import folder the program will log that there are no files to import.
The program will move any files in the "Import" folder to the "Trash" folder if the files do not end with .png, .zip or .bin and this move will be logged. 
The program will ignore any sub folders in the "Import" folder. 
The program will then  unzip any zipped files in the folder so that the files that are unzipped are still in the Import folder. 
If the files that are unzipped are already in the Import folder, then the existing file will be moved to the "Trash" folder and the move will be logged. 
If files that are unzipped do not have a .bin or .png file extention, then the files are moved to the "Trash" folder and the move is logged. 
Then it will move the .zip files into the "Imported" folder. 
Again, there are no files in the Import folder the program will log that there are no files to import.

2. Validating the .bin files in the Import folder. 
The .bin files are binary.
The first 32 bytes are file header bytes. Each binary file has only one header. 
After the header bytes there maybe one or more tuples. 
By 6 (index starts at zero) in the header is the count of how many tuples are in the file. 
Tuple that consists of the following columns:
1. split ID (1 byte)
2. Shard ID (1 byte)
3. Denomination (1 byte)
4. user ID (4 bytes)
5. 25 passwords (16 bytes each) for a total of 400 bytes. 
6. Status (13 bytes)
7. , and a user type, a date. 

The program must then write each coin to a file and put that file into the "Suspect" folder. 


The data types for the tuple are: 
user id: integrer
passwords: a string of 32 hexidecimal characters like a UUID. 
Status Indicator: a string of 25 characters. 
User type: an integer
Date: A timestamp that only includes that date and not the time. 

  that belong to that userid.
The files may contain one or more  
 

Files are read to see if they are valid. 
If valid, the files are moved to the "Suspect" folder. A copy of the file is put in the "Imported" folder.  
If not valid they are put in the "Trash" folder. 
If the file is already in the "suspect" folder then the one in the suspect folder is overwritten. 

2.  


nilufar Moghimi Archaeology
moghimin@yahoo.com
Joel.Palka@asu.edu

Dearh _____
Thank you very much for considereing collarborating wi

  <div>
            <img alt="Gold Plated Cloud Coin Logo" src="img/gold_cloudcoin_logo.png" style="width:90%; height:85%" /> <>
            <h3 class="featurwHeading">20,000<br>CloudCoin</h3>
            <p class="featurText">Buy 20,000 CloudCoins for $200.</p>                                                               <a class="btnCustom" href="https://transactions.sendowl.com/products/79141732/2C90BA20/add_to_cart" rel="no>
              <!--  <img src="img/addtocart.png" > --> <h3>Add to Cart</h3>
</a><script type="text/javascript" src="https://transactions.sendowl.com/assets/sendowl.js" ></script>                      </div>


Use Pandas Series to analyze sales data for a retail store over a week and draw insights from the data.


sales_data = [120, 150, 130, 170, 160, 180, 140]

days_of_week = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']

sales_data_with_index = pd.Series(sales_data, days_of_week)


stats =  sales_data_with_index.describe()


The client will do the following tasks:


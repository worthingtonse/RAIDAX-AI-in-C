# Prompt for creating a CloudCoin Client
## Overview: 

CloudCoins are files that contain a serial number and twenty five authenticity numbers. The authenticity numbers are GUIDs that act like passords. There a


# DEPOSIT 
Takes coins and changes their Authenticity numbers to change ownership. 

Process | Purpose
---|---
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


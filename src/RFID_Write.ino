#include <SPI.h>
#include <MFRC522.h>

String COUNTRY = "NL";
String BANK = "NSBA";


/*Using Hardware SPI of Arduino */
/*MOSI (11), MISO (12) and SCK (13) are fixed */
/*You can configure SS and RST Pins*/
#define SS_PIN 10  /* Slave Select Pin */
#define RST_PIN 9  /* Reset Pin */

/* Create an instance of MFRC522 */
MFRC522 mfrc522(SS_PIN, RST_PIN);
/* Create an instance of MIFARE_Key */
MFRC522::MIFARE_Key key;          

/* Set the block to which we want to write data */
/* Be aware of Sector Trailer Blocks */
int blockNum1 = 4;
int blockNum2 = 5;  
/* Create an array of 16 Bytes and fill it with data */
/* This is the actual data which is going to be written into the card */
byte firstData [16] = {};
byte secondData [16] = {};

/* Create another array to read data from Block */
/* Length of buffer should be 2 Bytes more than the size of Block (16 Bytes) */
byte bufferLen = 18;
byte readBlockData1[18];
byte readBlockData2[18];

String tag_UID = "";

MFRC522::StatusCode status;

String IBAN = "";
#define LENGTH 8

void setup() 
{
  /* Initialize serial communications with the PC */
  Serial.begin(9600);
  /* Initialize SPI bus */
  SPI.begin();
  /* Initialize MFRC522 Module */
  mfrc522.PCD_Init();
  Serial.println("Scan a MIFARE 1K Tag to write data...");
}

void loop()
{
  /* Prepare the key for authentication */
  /* All keys are set to FFFFFFFFFFFFh at chip delivery from the factory */
  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
  /* Look for new cards */
  /* Reset the loop if no new card is present on RC522 Reader */
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  
  /* Select one of the cards */
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("\n");
  Serial.println("**Card Detected**");
  /* Print UID of the Card */
  Serial.print(F("Card UID:"));
  if (tag_UID == "") {
    for (uint8_t i = 0; i < 4; i++) {
      tag_UID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Convert the UID to a single String
    }
    tag_UID.toUpperCase();
  }
  Serial.print("\n");
  Serial.println(tag_UID);
  /* Print type of card (for example, MIFARE 1K) */
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
         
  IBAN = "";
  unsigned long a = 0;
  for (int i = 0; i < LENGTH; i++) {
    unsigned long power = 1;
    for (int j = 0; j < i; j++) {
      power *= 16;
    }
    int stringToHex = (int)tag_UID[LENGTH - 1 - i] - '0';
    if (stringToHex > 9) {stringToHex -= 7;}

    a += stringToHex * power;
  }
  IBAN = (String)a;
  for (int x = 0; x < 10 - IBAN.length(); x++) {
    IBAN = '0' + IBAN;
  }
  Serial.print("IBAN = ");
  Serial.println(IBAN);
  char arr[16] = {};
  int nums[16] = {};
  IBAN.toCharArray(arr, 16);
  for (int z = 0; z < 16; z++) {
    nums[z] = (arr[z] <= '9' && arr[z] >= '0' ? (int)arr[z] - '0' : 0);
  }
  for (int y = 0; y < 10; y++) {
    secondData[y] = IBAN[y];
    Serial.println(secondData[y]);
  }

   /* Call 'WriteDataToBlock' function, which will write data to the block */
   Serial.print("\n");
   Serial.println("Writing to Data Block...");
   WriteDataToBlock(blockNum2, secondData);
   
   /* Read data from the same block */
   Serial.print("\n");
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock(blockNum2, readBlockData2);
   /* If you want to print the full memory dump, uncomment the next line */
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   
   /* Print the data read from block */
   Serial.print("\n");
   Serial.print("Data in Block:");
   Serial.print(blockNum2);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.print(readBlockData2[j]);
   }
   Serial.print("\n");

  

  int sum = 0;
  for (int u = 0; u < 16; u++) {
    sum += nums[u];
  }
  Serial.println(sum);
  String d = "";
  d += COUNTRY;
  d += (int)(sum/10);
  d += (int)(sum%10);
  d += BANK;
  Serial.println(d);
  for (int v = 0; v < 8; v++) {
    firstData[v] = d[v];
  }

  /* Call 'WriteDataToBlock' function, which will write data to the block */
   Serial.print("\n");
   Serial.println("Writing to Data Block...");
   WriteDataToBlock(blockNum1, firstData);
   
   /* Read data from the same block */
   Serial.print("\n");
   Serial.println("Reading from Data Block...");
   ReadDataFromBlock(blockNum1, readBlockData1);
   /* If you want to print the full memory dump, uncomment the next line */
   //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
   
   /* Print the data read from block */
   Serial.print("\n");
   Serial.print("Data in Block:");
   Serial.print(blockNum1);
   Serial.print(" --> ");
   for (int j=0 ; j<16 ; j++)
   {
     Serial.print(readBlockData1[j]);
   }
   Serial.print("\n");



   // WHEN READING CHECK IF IT FALLS WITHIN ASCII NUMBER RANGE FROM '0' TO '9' !!
}



void WriteDataToBlock(int blockNum, byte blockData[]) 
{
  /* Authenticating the desired data block for write access using Key A */
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Authentication failed for Write: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  
  /* Write data to the block */
  status = mfrc522.MIFARE_Write(blockNum, blockData, 16);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Writing to Block failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Data was written into Block successfully");
  }
  
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{
  /* Authenticating the desired data block for Read access using Key A */
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK)
  {
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }
  else
  {
    Serial.println("Authentication success");
  }

  /* Reading data from the Block */
  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK)
  {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else
  {
    Serial.println("Block was read successfully");  
  }
  
}
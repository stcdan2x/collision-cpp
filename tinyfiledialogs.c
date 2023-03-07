}
strcat(lDialogString, " \"");
if (aMessage && strlen(aMessage))
{
   strcat(lDialogString, aMessage);
}
strcat(lDialogString,
       "\" 0 0 >/dev/tty) 2>&1 ; ( echo $? ) 2>&1 ; echo >/dev/tty");
}
else if (notifysendPresent())
{
   strcpy(lDialogString, "notify-send \"");
   strcat(lDialogString, gTitle);
   strcat(lDialogString, "\n");
   strcat(lDialogString, gMessage);
   strcat(lDialogString, "\"");
}
else if (xmessagePresent())
{
   strcpy(lDialogString, "xmessage -center \"");
   strcat(lDialogString, gTitle);
   strcat(lDialogString, "\n");
   strcat(lDialogString, gMessage);
   strcat(lDialogString, "\"");
}
else
{
   printf("\n%s\n\n", gTitle);
   printf("%s\n", gMessage);
   return 0;
}

/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
if (!(lIn = popen(lDialogString, "r")))
{
   return 0;
}
while (fgets(lBuff, sizeof(lBuff), lIn) != NULL)
{
}
pclose(lIn);
/* printf ( "lBuff: %s len: %d \n" , lBuff , strlen(lBuff) ) ; //*/
if (lBuff[strlen(lBuff) - 1] == '\n')
{
   lBuff[strlen(lBuff) - 1] = '\0';
}
/* printf ( "lBuff1: %s len: %d \n" , lBuff , strlen(lBuff) ) ; //*/
lResult = strcmp(lBuff, "0") ? 0 : 1;
/* printf ( "lResult: %d\n" , lResult ) ; //*/
return lResult;
}

/* returns the hexcolor as a string "#FF0000" */
/* aoResultRGB also contains the result */
/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
/* aDefaultRGB and aoResultRGB can be the same array */
char const *tinyfd_colorChooser(
    char const *const aTitle,         /* NULL or "" */
    char const *const aDefaultHexRGB, /* NULL or "#FF0000"*/
    unsigned char aDefaultRGB[3],     /* { 0 , 255 , 255 } */
    unsigned char aoResultRGB[3])     /* { 0 , 0 , 0 } */
{
   static char lBuff[16];
   char lTmp[16];
   char lDialogString[MAX_PATH_OR_CMD];
   char lDefaultHexRGB[8];
   char *lpDefaultHexRGB;
   FILE *lIn;
   int lWasZenity3 = 0;
   int lWasOsascript = 0;

   lBuff[0] = '\0';

   if (aDefaultHexRGB)
   {
      Hex2RGB(aDefaultHexRGB, aDefaultRGB);
      lpDefaultHexRGB = (char *)aDefaultHexRGB;
   }
   else
   {
      RGB2Hex(aDefaultRGB, lDefaultHexRGB);
      lpDefaultHexRGB = (char *)lDefaultHexRGB;
   }

   if (zenity3Present())
   {
      lWasZenity3 = 1;
      sprintf(lDialogString,
              "zenity --color-selection --show-palette --color=%s", lpDefaultHexRGB);
      if (aTitle && strlen(aTitle))
      {
         strcat(lDialogString, " --title=\"");
         strcat(lDialogString, aTitle);
         strcat(lDialogString, "\"");
      }
   }
   else if (kdialogPresent())
   {
      sprintf(lDialogString,
              "kdialog --getcolor --default '%s'", lpDefaultHexRGB);
      if (aTitle && strlen(aTitle))
      {
         strcat(lDialogString, " --title \"");
         strcat(lDialogString, aTitle);
         strcat(lDialogString, "\"");
      }
   }
   else if (osascriptPresent())
   {
      lWasOsascript = 1;
      strcpy(lDialogString, "osascript -e 'tell app (path to frontmost \
application as Unicode text) to set mycolor to choose color default color {");
      sprintf(lTmp, "%d", 256 * aDefaultRGB[0]);
      strcat(lDialogString, lTmp);
      strcat(lDialogString, ",");
      sprintf(lTmp, "%d", 256 * aDefaultRGB[1]);
      strcat(lDialogString, lTmp);
      strcat(lDialogString, ",");
      sprintf(lTmp, "%d", 256 * aDefaultRGB[2]);
      strcat(lDialogString, lTmp);
      strcat(lDialogString, "}' ");
      strcat(lDialogString,
             "-e 'set mystring to ((item 1 of mycolor)/256 as integer) as string' ");
      strcat(lDialogString,
             "-e 'repeat with i from 2 to the count of mycolor' ");
      strcat(lDialogString,
             "-e 'set mystring to mystring & \" \" & \
((item i of mycolor)/256 as integer) as string' ");
      strcat(lDialogString, "-e 'end repeat' ");
      strcat(lDialogString, "-e 'mystring'");
   }
   else if (tkinter2Present())
   {
      strcpy(lDialogString, gPython2Name);
      if (!isatty(1))
      {
         strcat(lDialogString, " -i"); /* for osx without console */
      }

      strcat(lDialogString,
             " -c \"import Tkinter,tkColorChooser;root=Tkinter.Tk();root.withdraw();");

      if (osascriptPresent())
      {
         strcat(lDialogString,
                "import os;os.system('''osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
      }

      strcat(lDialogString, "res=tkColorChooser.askcolor(color='");
      strcat(lDialogString, lpDefaultHexRGB);
      strcat(lDialogString, "'");
      if (aTitle && strlen(aTitle))
      {
         strcat(lDialogString, ",title='");
         strcat(lDialogString, aTitle);
         strcat(lDialogString, "'");
      }
      strcat(lDialogString, ");\
\nif res[1] is not None:\n\tprint res[1]\"");
   }
   else if (zenityPresent())
   {
      strcpy(lDialogString, "zenity --entry");
      if (aTitle && strlen(aTitle))
      {
         strcat(lDialogString, " --title=\"");
         strcat(lDialogString, aTitle);
         strcat(lDialogString, "\"");
      }
      strcat(lDialogString, " --text=\"Enter hex rgb color\nie: #f5ca20\"");
      strcat(lDialogString, " --entry-text=\"");
      strcat(lDialogString, lpDefaultHexRGB);
      strcat(lDialogString, "\"");
   }
   else if (dialogPresent() || whiptailPresent())
   {
      if (dialogPresent())
      {
         strcpy(lDialogString, "(dialog ");
      }
      else
      {
         strcpy(lDialogString, "(whiptail ");
      }
      if (aTitle && strlen(aTitle))
      {
         strcat(lDialogString, "--title \"");
         strcat(lDialogString, aTitle);
         strcat(lDialogString, "\" ");
      }
      strcat(lDialogString,
             "--inputbox \"Enter hex rgb color\nie: #f5ca20\" 0 0 \"");
      strcat(lDialogString, lpDefaultHexRGB);
      strcat(lDialogString, "\" >/dev/tty) 2>&1 ; echo >/dev/tty");
   }
   else
   {
      tinyfd_messageDialog(gTitle, gMessage, "ok", "error", 1);
      return NULL;
   }
   /* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
   if (!(lIn = popen(lDialogString, "r")))
   {
      return NULL;
   }
   while (fgets(lBuff, sizeof(lBuff), lIn) != NULL)
   {
   }
   pclose(lIn);
   if (!strlen(lBuff))
   {
      return NULL;
   }
   /* printf ( "len Buff: %lu\n" , strlen(lBuff) ) ; //*/
   /* printf ( "lBuff0: %s\n" , lBuff ) ; //*/
   if (lBuff[strlen(lBuff) - 1] == '\n')
   {
      lBuff[strlen(lBuff) - 1] = '\0';
   }
   if (lWasZenity3)
   {
      lBuff[3] = lBuff[5];
      lBuff[4] = lBuff[6];
      lBuff[5] = lBuff[9];
      lBuff[6] = lBuff[10];
      lBuff[7] = '\0';
      Hex2RGB(lBuff, aoResultRGB);
   }
   else if (lWasOsascript)
   {
      sscanf(lBuff, "%hhu %hhu %hhu", &aoResultRGB[0], &aoResultRGB[1], &aoResultRGB[2]);
      RGB2Hex(aoResultRGB, lBuff);
   }
   else
   {
      Hex2RGB(lBuff, aoResultRGB);
   }
   /* printf("%d %d %d\n", aoResultRGB[0],aoResultRGB[1],aoResultRGB[2]); //*/
   /* printf ( "lBuff: %s\n" , lBuff ) ; //*/
   return lBuff;
}

#endif /* _WIN32 */

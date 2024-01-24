#include "iokit.h"

long SmaoReadSocket(SOCKET Socket, double * time){
    char line[512] = "Blank";
    char Msg[16384];
    char AckMsg[5] = "Ack\n";
    long Imsg,Iline;
    int NumBytes;

    memset(Msg,'\0',16384);

    NumBytes = recv(Socket,Msg,16384,0);
    if (NumBytes <= 0) return TRUE; /* Bail out if no message */

    Imsg = 0;
    Iline = 0;
    memset(line,'\0',512);
    while((Msg[Imsg] != '\n') && (Iline < 511) && (Imsg < 16383)) {
       line[Iline++] = Msg[Imsg++];
    }
    line[Iline++] = Msg[Imsg++];
    if (TRUE) printf("%s",line);

    double read_test=0;
    sscanf(line,"%le", &read_test);
    *time = read_test;

    /* Acknowledge receipt */
    send(Socket,AckMsg,strlen(AckMsg),0);
    return FALSE;
}

void SmaoWriteSocket(SOCKET Socket, double sendVal){
    int Success;
    char AckMsg[5] = "???\n";
    char Msg[16384];
    long MsgLen = 0;
    long LineLen;
    char line[512];

    sprintf(line,"%18.12le\n",sendVal);
    LineLen = strlen(line);
    memcpy(&Msg[MsgLen],line,LineLen);
    MsgLen += LineLen;

    sprintf(line,"[EOF]\n\n");
    LineLen = strlen(line);
    memcpy(&Msg[MsgLen],line,LineLen);
    MsgLen += LineLen;

    Success = send(Socket,Msg,MsgLen,0);

    /* Wait for Ack */
    recv(Socket,AckMsg,5,0);
    printf("Pro42 write sock, Smao ask: %s\n",AckMsg);
}

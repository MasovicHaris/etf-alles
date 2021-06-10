#include <iostream>
#include <fstream>
//#include <bits/stdc++.h>
#include <sys/stat.h>
#include<string>
#include<bitset>
#include<dirent.h>
#include<vector>
#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>
#include<sstream>
#include <cmath>

using namespace std;
unsigned short int mem[65536]={0x0000}, regs[16], noOfInstructions; // regs[15] je PC
int fileModes[16], openModes[16], lseekpos[16], fd;

void setRegsToZero(){
    for(int i = 0; i < 16; i++){
        regs[i] = 0;
    }
}

void populateOpenModes(){
    openModes[0] = 0;//O_RDONLY
    openModes[1] = 1;//O_WRONLY
    openModes[2] = 2;//O_RDWR
    openModes[3] = 8;//O_APPEND
    openModes[4] = 256;//O_CREAT
    openModes[5] = 512;//O_TRUNC
    openModes[6] = 1024;//O_EXCL
    openModes[7] = 0;//Defaultni mode
    openModes[8] = 0;
    openModes[9] = 0;
    openModes[10] = 0;
    openModes[11] = 0;
    openModes[12] = 0;
    openModes[13] = 0;
    openModes[14] = 0;
    openModes[15] = 0;
}

void populateFileModes(){
    fileModes[0] = 64;//S_IXUSR
    fileModes[1] = 128;//S_IWUSR
    fileModes[2] = 256;//S_IRUSR
    fileModes[3] = 448;//S_IRWXU
    fileModes[4] = 256;//Defaultna vrijednost u slicaju da je rijec registra R2 veca od 4;
    fileModes[5] = 256;
    fileModes[6] = 256;
    fileModes[7] = 256;
    fileModes[8] = 256;
    fileModes[9] = 256;
    fileModes[10] = 256;
    fileModes[11] = 256;
    fileModes[12] = 256;
    fileModes[13] = 256;
    fileModes[14] = 256;
    fileModes[15] = 256;


    //Napomena: Neki mode/privilegije koji su podržani u unix sistemima, nisu podržani u windowsu.
    //Također, neki mode/privilegije su podržane u nekim kompajlerima
    //https://www.ibm.com/support/knowledgecenter/SSLTBW_2.2.0/com.ibm.zos.v2r2.bpxbd00/rtcre.htm


}


void populateLseeekPos(){
    lseekpos[0] = 0; //SEEK_SET
    lseekpos[1] = 1;//SEEK_CUR
    lseekpos[2] = 2;//SEEK_END
    lseekpos[3] = 0;
    lseekpos[4] = 0;
    lseekpos[5] = 0;
    lseekpos[6] = 0;
    lseekpos[7] = 0;
    lseekpos[8] = 0;
    lseekpos[9] = 0;
    lseekpos[10] = 0;
    lseekpos[11] = 0;
    lseekpos[12] = 0;
    lseekpos[13] = 0;
    lseekpos[14] = 0;
    lseekpos[15] = 0;
}

void loadInstructions(){
    std::fstream memFile;
    memFile.open("mem.txt", std::fstream::in|std::fstream::out|std::fstream::app);
    unsigned short int instr;
    while(memFile >> std::hex >> instr){
        mem[noOfInstructions] = instr;
        noOfInstructions++;
    }

}



std::string readFromMemory(int address, int numberOfBtyes = 0) {
    std::string naziv="";
    //Provjeriti uslove
    char firstCharacter = (0x00);
    char secondCharacter = (0x00);
    int charactersRead = 0;

    do {
        auto value = mem[address];
        firstCharacter = char((value >> 8) & 0x00FF);
        secondCharacter = char(value & 0x00FF);

        if(firstCharacter != (0x00)) {
            charactersRead++;
            if(numberOfBtyes != 0 && charactersRead > numberOfBtyes) break;
            naziv += firstCharacter;

            if(secondCharacter != (0x00)) {
                charactersRead++;
                if(numberOfBtyes != 0 && charactersRead > numberOfBtyes) break;
            }
            naziv += secondCharacter;
        }
        address++;
    } while(firstCharacter != (0x00));

    return naziv;
}

void writeToMemory(int whereToWrite, std::string stringToWrite, int numberOfBtyes = 0) {

    if(numberOfBtyes > stringToWrite.size())
        return;

    unsigned int velicina = stringToWrite.size();
    bool kontrolna = false;
    if(numberOfBtyes != 0) {
        velicina = numberOfBtyes;
        if(numberOfBtyes % 2 != 0) {
            kontrolna = true;
            velicina++;
        }

    }

    for(unsigned int i = 0; i < velicina; ++i) {
        short int twoChars = (char(stringToWrite[i]) << 8);

        if(i == velicina - 1 && kontrolna) {
            mem[whereToWrite] = twoChars;
            break;
        }

        if((i + 1) < velicina) {
            twoChars =  (twoChars | char(stringToWrite[i+1]));
            i++;
        }

        mem[whereToWrite] = twoChars;
        if((i + 1) < velicina) {
            whereToWrite++;
        }
    }
    if(velicina % 2 != 0 || kontrolna) mem[whereToWrite] = mem[whereToWrite] & 0xFF00;
    else mem[++whereToWrite] = 0x0000;
}

void interpret(){
    int i = 0;
    unsigned short int opcode, r, n, k;
    bool r1, n1;
    while (i <= noOfInstructions){
        // opcode je cijela istrukcija kodirana kao OP|DEST|SRC1|SRC2
        opcode = mem[regs[15]++];

        switch(opcode & 0xF000){
            case 0x0000:
                regs[(opcode>>8) & 0x000F] = regs[opcode & 0x000F];
                break;
            case 0x1000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] + regs[opcode & 0x000F];
                break;
            case 0x2000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] - regs[opcode & 0x000F];
                break;
            case 0x3000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] & regs[opcode & 0x000F];
                break;
            case 0x4000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] | regs[opcode & 0x000F];
                break;
            case 0x5000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] ^ regs[opcode & 0x000F];
                break;
            case 0x6000:
                r = regs[opcode & 0x000F];
                n = (r & 0x000F);
                if (((r >> 4) & 0x0003) == 0){
                    k = (regs[(opcode >>4) & 0x000F] | 0x7FFF);
                    // odredjivanje je li 1 najveci bit, ako je 1 mora se dodati 1 na kraj, a ako je 0, obicni shift ce svakako dodati nulu
                    regs[(opcode>>8) & 0x000F] = k == 0xFFFF ?  (regs[(opcode>>4) & 0x000F] >> n) & ~(((0x1 << 16) >> n) << 1) : regs[(opcode>>4) & 0x000F] >> n;
                }
                else if (((r >> 4) & 0x0003) == 1) regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] >> n;
                else if (((r >> 4) & 0x0003) == 2) regs[(opcode>>8) & 0x000F] = (regs[(opcode>>4) & 0x000F] << n) | (regs[(opcode>>4) & 0x000F] >> (16 - n));
                else regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] << n;
                break;
            case 0x7000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] * regs[opcode & 0x000F];
                break;
            case 0x8000:
                mem[regs[opcode & 0x000F]] = regs[(opcode>>4) & 0x000F];
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F];
                cout <<(char)((mem[regs[7]]>>8)&0x00FF) <<(char)(mem[regs[7]]&0x00FF)<< " ";
                break;
            case 0x9000:
                k = opcode & 0x00FF;
                regs[(opcode>>8) & 0x000F] = k;
                break;
            case 0xA000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] > regs[opcode & 0x000F] ? 0x0001 : 0x0000;
                break;
            case 0xB000:
                r = regs[(opcode >> 4) & 0x000F];
                n = regs[ opcode & 0x000F];
                r1 = (r & 0x8000)==0x0000 ? false : true;
                n1 = (n & 0x8000)==0x0000 ? false : true;
                if(r1 && !n1){
                    regs[(opcode >> 8) & 0x000F] = 0x0001;
                }
                else if(!r1 && n1){
                    regs[(opcode >> 8) & 0x000F] = 0x0000;
                }
                else{
                   regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] > regs[opcode & 0x000F] ? 0x0001 : 0x0000;
                }
                break;
            case 0xC000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] < regs[opcode & 0x000F] ? 0x0001 : 0x0000;
                break;
            case 0xD000:
                r = regs[(opcode >> 4) & 0x000F];
                n = regs[ opcode & 0x000F];
                r1 = (r & 0x8000)==0x0000 ? false : true;
                n1 = (n & 0x8000)==0x0000 ? false : true;
                if(r1 && !n1){
                    regs[(opcode >> 8) & 0x000F] = 0x0000;
                }
                else if(!r1 && n1){
                    regs[(opcode >> 8) & 0x000F] = 0x0001;
                }
                else{
                   regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] < regs[opcode & 0x000F] ? 0x0001 : 0x0000;
                }
                break;
            case 0xE000:
                regs[(opcode>>8) & 0x000F] = regs[(opcode>>4) & 0x000F] == regs[opcode & 0x000F] ? 0x0001 : 0x0000;
                break;
            case 0xF000:
                regs[(opcode >> 8) & 0x000F] = regs[15];
                regs[15] = opcode & 0x000F;
                int ret;
                if(regs[15] == 0x000F){
                    //SISTEMSKI POZIVI
                    string fn;
                    string nazivFilea;
                    int postoji;
                    switch(regs[0] & 0x0007){

                    case 0x0000:

                            nazivFilea = "./storage/"+readFromMemory(regs[1]);
                            cout<<"Naziv fajla: "<< nazivFilea<<endl;
                            struct stat buff;
                            postoji = stat(nazivFilea.c_str(), &buff);
                            if(postoji == 0){
                                cout << "Datoteka ili direktorij pronadjen!" << endl;
                                cout << "Atributi za datoteku ili direktorij "<< nazivFilea << " su:" << endl;
                                cout << "Mode: " << buff.st_mode << endl;
                                cout << "Id filea: "<< buff.st_ino << endl;
                                cout << "Id ownera filea: "<< buff.st_uid<< endl;
                                cout << "Velicina bajti za fajl/ broj bajtova alociran za direkorij: "<<buff.st_size<< endl;
                                cout << "Posljednji pristup: "<< buff.st_atime<< endl;
                                cout << "Posljednji put kada je promjena napravljenja: "<< buff.st_mtime<< endl;
                                //cout << "Velicina bloka u bajtovima za fajl: " << buff.st_blksize;
                            }
                            else{
                                cout << "Datoteka ili direktorij sa nazivom: "<< nazivFilea << " nije pronadjena."<<endl;
                            }


                        break;
                    case 0x0001:
                        fn = "./storage/" + readFromMemory(regs[1]);
                        if ((fd = creat(fn.c_str(), fileModes[regs[2]&0x000F] | fileModes[(regs[2]>>4)&0x000F] | fileModes[(regs[2]>>8)&0x000F] |fileModes[(regs[2]>>12)&0x000F])) < 0)
                            perror("creat() error");
                        else {
                            regs[1]=fd;
                            cout<<"Datoteka sa nazivom: "<< fn << " kreirana!"<<endl;
                        }
                        break;

                    case 0x0002:
                        fn = "./storage/" + readFromMemory(regs[1]);
                        if ((fd = open(fn.c_str(), openModes[regs[2]&0x000F] | openModes[(regs[2]>>4)&0x000F] | openModes[(regs[2]>>8)&0x000F] |openModes[(regs[2]>>12)&0x000F])) < 0)
                            perror("open() error");
                        else {
                            regs[1]=fd;
                            cout<<"Datoteka sa nazivom: "<< fn << " otvorena!"<<endl;
                        }
                        break;
                    case 0x0003:

                        if(regs[1] != 0){
                            close(regs[1]);
                            cout<<"Datoteka zatvorena.\n";
                        }
                        else{
                            cout << "Greska pri zatvaranju datoteke, fd=0;\n";
                        }
                        break;
                    case 0x0004:
                        fn = "./storage/" + readFromMemory(regs[1]);
                        if (unlink(fn.c_str()) != 0)
                            perror("unlink() error");
                        else{
                            cout<< "Datoteka sa nazivom: "<<fn << " unlinkovana!"<<endl;
                        }
                        break;
                    case 0x0005:
                        if(regs[1]<0){
                            cout << "Nijedna datoteka nije otvorena";
                        }

                        else{
                            char buff[1024];
                            if((ret = read(regs[1], buff, regs[3]))>0){
                                cout << "Ocitani blok: \n"<<buff<<"\n";
                                string stringZaUpisati = buff;
                                writeToMemory(regs[2],stringZaUpisati,regs[3]);
                            }
                            else{
                                cout << "Greska pri citanju bloka\n";
                            }
                        }
                        break;
                    case 0x006:
                            if(regs[1]<0){
                            cout << "Nijedna datoteka nije otvorena\n";
                        }
                        else{

                            string stringZaUpis = readFromMemory(regs[2],regs[3]);
                            char stringZaUpisChar[3];
                            for (int i = 0; i < stringZaUpis.length(); i++) {
                                stringZaUpisChar[i] = stringZaUpis[i];
                            }
                            if((ret = write(regs[1], stringZaUpisChar, regs[3]))==-1){
                                cout << "Upisivanje u datoteku nije uspjelo.\n";
                            }
                            else{
                                cout << "Broj upisanih bajta: "<<ret<<"\n";
                            }
                        }
                        break;
                    case 0x007:
                        if(regs[1]<0){
                            cout<<"Nijedna datoteka nije otvorena\n";
                        }
                        else{
                            ret=lseek(regs[1], regs[2], lseekpos[regs[3] & 0x000F]);
                            if(ret==-1){
                                cout<<"Promjena offseta nije uspjela!\n";
                            }
                            else{
                                cout<<"Uspjesno promjenjen offset. Trenutna vrijednost: "<<ret<<".\n";
                            }
                        }
                        break;

                }

        }
                regs[15] = regs[(opcode >> 8) & 0x000F];
                break;
    }
    ++i;
}

}

int main()
{

    //Provjeriti da li fali populateOpenModes();
    populateOpenModes();
    populateLseeekPos();
    populateFileModes();
    setRegsToZero(); //PC postavimo na nultu poziciju
    loadInstructions(); //Očitavamo instrukcije iz mem.txt

    interpret();

    /* primjer citanja i pisanja u memoriju sa full vrijednostima i kad se proslijeduju broj bajta
     1 bajt = 1 char

    std::string novi = { "masha1.txt" };
    short int adresa = 10;
    writeToMemory(adresa, novi);

    std::cout << readFromMemory(adresa,5);

     */

    /*
    int ret,fd;
    int a=3;
    char buf[a];
    char c[1024];
    if((fd = open("./storage/masha.txt", O_RDONLY))<0){
        cout << "err";
    }
    else{
        if((ret=read(fd,buf,a))>0){
            cout << buf << "\n" ;
        unsigned short int neki= buf[0];
        neki = (neki<<8) + buf[1];
        char p1 = neki & 0x00FF;
        char p2 = (neki >>8) & 0x00FF;
        cout<<p1 <<" " << p2;

        }
        close(fd);
       // unlink("./storage/nele.txt");
    }
    */
    return 0;
}

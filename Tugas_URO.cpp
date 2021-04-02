#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
using namespace std;
int maks_x=20; int maks_y=10; int maks_kecoak=15; int jangkauan_robot=5;
string pesan_output=" ";

//object kecoak
class Kecoak{
	//definisikan atribut kecoa
    public:
        int x; int y; int health; int damage; int jangkauan_serang; bool isMati;
    public:
    	//inisialisasi keadaan kecoa
        Kecoak(){
            x = 1 + rand() % maks_x+1;
            y = 1 + rand() % maks_y+1;
            health=3; damage=1;
            jangkauan_serang = 2;
            isMati = false;
        }
        //gerak kecoa yang random
        void kecoak_bergerak(){
            int move_1 = -1 + (rand()%3);
            int move_2 = -1 + (rand()%3);
			if ((x + move_1 >= 0) && (x + move_1 <= maks_x)){
                x += move_1;
            }
            if ((y + move_2 >= 0) && (y + move_2 <= maks_y)){
                y += move_2;
            }
        }
        //kalau kecoa mati
        void cek_mati(){
            if (health<=0){isMati=true;}
        }
};
//object robot
class Robot{
    public:
        int x; int y; int health; int damage;
    public:
    	//inisialisasi
        Robot(){
            setting_awal();
        }
        //penghitung jarak robot kecoa
        float jarak_robot_kecoak(Kecoak kecoak){
            float x2=(kecoak.x - x);
            float y2=(kecoak.y - y);
            return sqrt(x2*x2 + y2*y2);

        }
        //boolean yang memberi informasi apakah robot mati atau tidak
        bool isRobotMati(){
                if (health<=0){return true;}
                else{return false;}
        }
        //pengatur gerak robot
        void robot_bergerak(char control){
            if (control == 'w'){
                if ((y+1)>maks_y){pesan_output="Tidak bisa bergerak karena akan di luar batas grid\n";}
                else{y++;}
            }
            if (control == 's'){
                if (y-1 < 0){pesan_output="Tidak bisa bergerak karena di luar batas grid\n";}
                else{y--;}
            }
            if (control == 'd'){
                if ((x+1)>maks_x){pesan_output="Tidak bisa bergerak karena di luar batas grid\n";}
                else{x++;}
            }
            if (control == 'a'){
                if ((x-1) < 0){pesan_output="Tidak bisa bergerak karena di luar batas grid\n";}
                else{x--;}
            }
        }
    private:
        void setting_awal(){
            x=0; y=0; health=10; damage=2;
        }
};
Robot robotku;
//mekanisme program
class Mekanisme{
    public: //karakter di program
        int jumlah_kecoak;
        Kecoak arr_kecoak[128];
    public: //inisialisasi kecoa
        Mekanisme(){
            jumlah_kecoak = rand() % maks_kecoak;
            antisipasi_duplikat();
        } //program mencetak kecoa
        void printing_x_kecoak(){
            for(int i=0;i<jumlah_kecoak;i++){
                cout << arr_kecoak[i].x << " " << i << endl;
            }
        }
        //kondisional serangan robot
        void robot_menyerang(){
            int indeks_kecoak_diserang[jumlah_kecoak];
            bool ada_serangan=false;
            int j=0;
            for(int i=0; i<jumlah_kecoak; i++){
                if ((robotku.jarak_robot_kecoak(arr_kecoak[i]) <= jangkauan_robot) && (not arr_kecoak[i].isMati)){
                    ada_serangan = true;
                    indeks_kecoak_diserang[j] = i;
                    j++;
                }
            }
            //apabila robot menyerang kecoa dalam jangkauan
            if (ada_serangan){
                int indeks_yang_diserang = rand()%j; //kecoa yang diserang random
                arr_kecoak[indeks_kecoak_diserang[indeks_yang_diserang]].health -= robotku.damage;
                arr_kecoak[indeks_kecoak_diserang[indeks_yang_diserang]].cek_mati();
                if (arr_kecoak[indeks_kecoak_diserang[indeks_yang_diserang]].isMati){
                    if (jumlah_kecoa_hidup() == 0){ //kecoa habis
                        pesan_output="Semua Kecoak telah musnah\n";
                    }
                    else{ //kecoa belum habis
                        stringstream ss;
                        ss<<jumlah_kecoa_hidup();
                        pesan_output = "1 Kecoak telah tumbang, tersisa "+ss.str()+" Kecoak lagi\n";
                    }
                }
            }
            else{ //kecoa diliuar jangkauan
                pesan_output = "Kecoak berada di luar jangkauan\n";
            }
        }
        void kecoak_menyerang(){ //serangan kecoa
            for (int i=0; i<jumlah_kecoak; i++){
                if (not arr_kecoak[i].isMati){
                    if (robotku.jarak_robot_kecoak(arr_kecoak[i]) <= arr_kecoak[i].jangkauan_serang){
                        robotku.health -= arr_kecoak[i].damage;
                    }
                }
            }
        }
        int jumlah_kecoa_hidup(){ //program untuk memanggil kecoa yang idup
            int count=0;
            for(int i=0;i<jumlah_kecoak;i++){
                if (not (arr_kecoak[i].isMati)){count++;}
            }
            return count;
        }
        void info(){ //info
            cout << "======INFO======\n";
            cout << "--Robot \n";
            printf("Koordinat = (%d,%d)\n",robotku.x,robotku.y);
            printf("Health = %d\n",robotku.health);
            printf("Damage = %d\n",robotku.damage);
            printf("Jangkauan Serang = %d\n",jangkauan_robot);
            int j=1;
            for (int i=0;i<jumlah_kecoak;i++){
                if (not (arr_kecoak[i].isMati)){
                    printf("--Kecoak %d\n",j);
                    printf("Koordinat = (%d,%d)\n",arr_kecoak[i].x,arr_kecoak[i].y);
                    printf("Health = %d\n",arr_kecoak[i].health);
                    printf("Damage = %d\n",arr_kecoak[i].damage);
                    printf("Jangkauan Serang = %d\n",arr_kecoak[i].jangkauan_serang);
                    j++;
                }
            }
            printf("\n");
        }
        void sorting(Kecoak kecoak[128],int panjang_array){ //sorting kecoa berdasar jarak
            for(int i=0; i<panjang_array; i++){
                float min = robotku.jarak_robot_kecoak(kecoak[i]);
                bool found = false;
                int k;
                for(int j=i; j<panjang_array; j++){
                    if (robotku.jarak_robot_kecoak(kecoak[j]) < min){
                        min = robotku.jarak_robot_kecoak(kecoak[j]);
                        k = j;
                        found = true;
                    }
                }
                if (found){
                    Kecoak temp = kecoak[i];
                    kecoak[i] = kecoak[k];
                    kecoak[k] = temp;
                    
                }
            }
        }
        void kalkulasi_jarak(){ //hitung jarak
            Kecoak kumpulan_kecoak[128];
            int j=0;
            for (int i=0;i<jumlah_kecoak;i++){
                if (not arr_kecoak[i].isMati){
                    kumpulan_kecoak[j] = arr_kecoak[i];
                    j++;
                }
            }
            sorting(kumpulan_kecoak,j);
            cout<<"======JARAK-JARAK KECOAK======\n";
            for (int i=0; i<j; i++){
                printf("--Kecoak %d\n",i+1);
                printf("Koordinat Kecoak = (%d,%d)\n",kumpulan_kecoak[i].x,kumpulan_kecoak[i].y);
                printf("Jarak Kecoak = %.2f\n",robotku.jarak_robot_kecoak(kumpulan_kecoak[i]));
            }
            printf("\n");
        }
        void peta(){ //buat peta dalam array
            int baris=maks_y+1;
            int kolom=maks_x+1;
            string grid[baris][kolom];
            for(int i=0;i<baris;i++){
                for(int j=0;j<kolom;j++){
                    grid[i][j]=" .";
                }
            }
            for (int i=0;i<baris;i++){
                grid[i][0]="|";
            }
            for (int j=0;j<kolom;j++){
                grid[baris-1][j]="--";
            }
            grid[baris-1-robotku.y][robotku.x] = " R";
            for(int i=0; i<jumlah_kecoak; i++){
                if (not arr_kecoak[i].isMati){
                    int komp_x=baris-1-arr_kecoak[i].y;
                    int komp_y=arr_kecoak[i].x;
                    grid[komp_x][komp_y] = " K";
                }
            }
            for(int i=0;i<baris;i++){
                for(int j=0;j<kolom;j++){
                    cout<<grid[i][j];
                }
                cout<<endl;
            }
        }
        void kontrol_gerak_robot(char inputan){ //kondisional gerak robot
            Robot coba_robot=robotku;
            coba_robot.robot_bergerak(inputan);
            bool is_sama=false;
            for (int i=0; i<jumlah_kecoak; i++){
                if ((coba_robot.x==arr_kecoak[i].x) && (coba_robot.y==arr_kecoak[i].y) && (not arr_kecoak[i].isMati)){
                    is_sama=true;
                }
            }
            if (not is_sama){
                robotku.robot_bergerak(inputan);
            }
			else {
				pesan_output ="Gerakan tidak valid. Robot menabrak kecoa\n";
			}    
        }
        void antisipasi_duplikat(){ //untuk menghindari kecoa tabrakan
            for (int i=0; i<jumlah_kecoak; i++){
                for (int j=0; j<jumlah_kecoak; j++){
                    if ((arr_kecoak[j].x == arr_kecoak[i].x) && (arr_kecoak[j].y == arr_kecoak[i].y) && (j!=i)){
                        while ((arr_kecoak[j].x == arr_kecoak[i].x) && (arr_kecoak[j].y == arr_kecoak[i].y)){
                            arr_kecoak[j].x = 1 + rand() % maks_x+1;
                            arr_kecoak[j].y = 1 + rand() % maks_y+1;
                        }
                    }
                }
            }
        }
        void kontrol_gerak_kecoak(){ //mengontrol gerak kecoa
            for (int i=0; i<jumlah_kecoak; i++){
                Kecoak coba_kecoak = arr_kecoak[i];
                coba_kecoak.kecoak_bergerak();
                bool is_sama=false;
                if ((coba_kecoak.x==robotku.x) && (coba_kecoak.y==robotku.y)){
                    is_sama=true;
                }
                for (int j=0; j<jumlah_kecoak; j++){
                    if ((coba_kecoak.x==arr_kecoak[j].x) && (coba_kecoak.y==arr_kecoak[j].y) && (not arr_kecoak[j].isMati) && (j!=i)){
                        is_sama=true;
                    }
                }
                if (not is_sama){
                    arr_kecoak[i].x=coba_kecoak.x;
                    arr_kecoak[i].y=coba_kecoak.y;
                }
            }
        }
        bool robot_mati(){ //bool untuk mengecek apakah robot mati
        if (robotku.isRobotMati()){return true;}
        else{return false;}
    }
};

int main() {
    Mekanisme mekanismeku;
    char command;
    while(command != 'p' && !robotku.isRobotMati() && mekanismeku.jumlah_kecoa_hidup()!=0 ){
        mekanismeku.peta();
        if (command == 'i'){
            system("cls"); 
            mekanismeku.info();
        }
        if (command == 'j'){
            system("cls"); 
            mekanismeku.kalkulasi_jarak();
        }
        //beri pesan output
        cout <<pesan_output;
        pesan_output = " ";
        printf("Health: %d\n",robotku.health);
        cout << "command: "; cin>>command;
        if ((command == 'a') || (command == 'w') || (command == 's') || (command =='d')){
            mekanismeku.kontrol_gerak_robot(command);
            mekanismeku.kecoak_menyerang();
            mekanismeku.kontrol_gerak_kecoak();
            system("cls"); 
        }
        else if (command == 't')
        {
            mekanismeku.robot_menyerang();
            mekanismeku.kecoak_menyerang();
            mekanismeku.kontrol_gerak_kecoak();
            system("cls");
        }
        else
        {
            if ((command =='i') || (command =='j')){continue;}
            pesan_output = "Input tidak dikenali\n";
            mekanismeku.kecoak_menyerang();
            mekanismeku.kontrol_gerak_kecoak();
            system("cls");
        }
    }
    printf("Anda telah membunuh %d kecoa\n",mekanismeku.jumlah_kecoak-mekanismeku.jumlah_kecoa_hidup());
    if(command=='p') {
    	printf("Anda telah keluar. Terimakasih telah bermain\n");
	}
    else if (robotku.isRobotMati()) {
    	printf("Maaf. Robot telah mati. Silahkan coba lagi\n");
	}
	else {
		printf("Selamat! Anda telah menang :D\n");
	}
	
    return 0;
}

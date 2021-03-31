#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
int maks_x=20; int maks_y=10; int maks_kecoak=15; int jangkauan_robot;
string pesan_output=" ";
class Kecoak{
    public:
        int x; int y; int health; int damage; int jangkauan_serang; bool isMati;
    public:
        Kecoak(){
            x = 1 + rand() % maks_x+1;
            y = 1 + rand() % maks_y+1;
            health=3; damage=1;
            jangkauan_serang = 2;
        }
        bool isKecoakMati(){
            if (health==0){return true;}
            else{return false;}
        }
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
        void cek_mati(){
            if (health<=0){isMati=true;}
        }
};

class Robot{
    public:
        int x; int y; int health; int damage;
    public:
        Robot(){
            setting_awal();
        }
        float jarak_robot_kecoak(Kecoak kecoak){
            float x2=(kecoak.x - x);
            float y2=(kecoak.y - y);
            return sqrt(x2*x2 + y2*y2);

        }
        bool isRobotMati(){
                if (health==0){return true;}
                else{return false;}
        }
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
class Mekanisme{
    public:
        int jumlah_kecoak;
        Kecoak arr_kecoak[128];
    public:
        Mekanisme(){
            jumlah_kecoak = rand() % maks_kecoak;
            antisipasi_duplikat();
        }
        void printing_x_kecoak(){
            for(int i=0;i<jumlah_kecoak;i++){
                cout << arr_kecoak[i].x << " " << i << endl;
            }
        }
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
            if (ada_serangan){
                int indeks_yang_diserang = rand()%(j+1);
                arr_kecoak[indeks_kecoak_diserang[indeks_yang_diserang]].health -= robotku.damage;
                arr_kecoak[indeks_kecoak_diserang[indeks_yang_diserang]].cek_mati();
            }
            else{
                cout << "Kecoak berada di luar jangkauan\n";
            }
        }
        void kecoak_menyerang(){
            for (int i=0; i<jumlah_kecoak; i++){
                if (not arr_kecoak[i].isMati){
                    if (robotku.jarak_robot_kecoak(arr_kecoak[i]) <= arr_kecoak[i].jangkauan_serang){
                        robotku.health -= arr_kecoak[i].damage;
                    }
                }
            }
        }
        int jumlah_kecoa_hidup(){
            int count=0;
            for(int i=0;i<jumlah_kecoak;i++){
                if (not (arr_kecoak[i].isMati)){count++;}
            }
            return count;
        }
        void info(){
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
        }
        void sorting(Kecoak kecoak[128],int panjang_array){
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
        void kalkulasi_jarak(){
            Kecoak kumpulan_kecoak[128];
            int j=0;
            for (int i=0;i<jumlah_kecoak;i++){
                if (not arr_kecoak[i].isMati){
                    kumpulan_kecoak[j] = arr_kecoak[i];
                    j++;
                }
            }
            sorting(kumpulan_kecoak,j);
            for (int i=0; i<j; i++){
                printf("--Kecoak %d\n",i+1);
                printf("Koordinat Kecoak = (%d,%d)\n",kumpulan_kecoak[i].x,kumpulan_kecoak[i].y);
                printf("Jarak Kecoak = %.2f\n",robotku.jarak_robot_kecoak(kumpulan_kecoak[i]));
            }
        }
        void peta(){
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
        void kontrol_gerak_robot(char inputan){
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
        }
        void antisipasi_duplikat(){
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
        void kontrol_gerak_kecoak(){
            for (int i=0; i<jumlah_kecoak; i++){
                Kecoak coba_kecoak = arr_kecoak[i];
                coba_kecoak.kecoak_bergerak();
                bool is_sama=false;
                if ((coba_kecoak.x==robotku.x) && (coba_kecoak.y==robotku.y)){
                    pesan_output="sama";
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
};

int main() {
    Mekanisme mekanismeku;
    char command;
    while(command != 'p'){
        mekanismeku.peta();
        if (command == 'i'){
            system("cls"); 
            mekanismeku.info();
        }
        if (command == 'j'){
            mekanismeku.kalkulasi_jarak();
        }
        printf("\n");
        cout <<pesan_output;
        pesan_output = " ";
        cout << "command: "; cin>>command;
        if ((command == 'a') || (command == 'w') || (command == 's') || (command =='d')){
            mekanismeku.kontrol_gerak_robot(command);
            mekanismeku.kecoak_menyerang();
            mekanismeku.kontrol_gerak_kecoak();
            system("cls"); 
        }
    }
    return 0;
}

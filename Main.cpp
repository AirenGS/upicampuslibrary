#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <cstring>  
#include <limits>
#include <stdio.h>
#include <vector>

using namespace std;
struct buku{
    string judul, pengarang, kode, status; 
};

struct mahasiswa{
    string nama, password, NIM; 
};

// Akun Petugas
string petUsername = "admin"; 
string petPassword = "admin"; 
// Active User
string logUsername, username, logPassword, password, nama, line;

string fullDate[3];
int dateNow[3], dateNext[3];

int tanggalMaker(){
    int i = 0;
    char str[] = __DATE__;
    char *token = strtok(str, " ");
    while (token != NULL)
    {
        fullDate[i] = token;
        token = strtok(NULL, " ");
        i++;
    }

    int hari = stoi(fullDate[1]);
    int bulan, tahun = stoi(fullDate[2]);
    int hariNext, bulanNext, tahunNext;

    if (fullDate[0] == "Jan") {
        bulan = 1;
    } else if (fullDate[0] == "Feb") {
        bulan = 2;
    } else if (fullDate[0] == "Mar") {
        bulan = 3;
    } else if (fullDate[0] == "Apr") {
        bulan = 4;
    } else if (fullDate[0] == "May") {
        bulan = 5;
    } else if (fullDate[0] == "June") {
        bulan = 6;
    } else if (fullDate[0] == "July") {
        bulan = 7;
    } else if (fullDate[0] == "Aug") {
        bulan = 8;
    } else if (fullDate[0] == "Sept") {
        bulan = 9;
    } else if (fullDate[0] == "Oct") {
        bulan = 10;
    } else if (fullDate[0] == "Nov") {
        bulan = 11;
    } else if (fullDate[0] == "Dec") {
        bulan = 12;
    }
    
    hariNext = hari + 7;
    if (hariNext > 28 && bulan == 2) {
        hariNext -= 28;
        bulanNext = bulan + 1;
    } else if (hariNext > 31 && bulan % 2 == 0 && bulan != 2) {
        hariNext += 31;
        bulanNext = bulan + 1;
    } else if (hariNext <= 31 && bulan % 2 == 0 && bulan != 2) {
        bulanNext = bulan;
    } else if (hariNext > 30 && bulan % 2 == 1 && bulan != 2) {
        hariNext -= 30;
        bulanNext = bulan + 1;
    }  else if (hariNext <= 30 && bulan % 2 == 1 && bulan != 2) {
        bulanNext = bulan;
    } 

    if (bulan > 12) {
        bulanNext -= 1;
        tahunNext = tahun + 1;
    } else {
        tahunNext = tahun;
    }

    dateNow[0] = bulan;
    dateNow[1] = hari;
    dateNow[2] = tahun;

    dateNext[0] = bulanNext;
    dateNext[1] = hariNext;
    dateNext[2] = tahunNext;
    
    for (int i = 0; i < 3; i++)
    {
        cout << dateNext[i] << " ";
    }
}

int menu();
int menuPetugas();
int menuMahasiswa();
int menuBuku();
int daftarBuku();
void login();
void registrasi();

int main()
{
    HOME:
    system("cls");
    int pilih = menu();
    tanggalMaker();
    system("pause");
    switch (pilih)
    {
    case 1:
        registrasi();
        break;
    case 2: 
        login();
        break;
    case 3:
        return 0;
    default:
        {
            cout << "Masukan pilihan yang valid" << endl;
            system("pause");
            main();
            break;
        }
    }
    label_pilih:
    int pilih2;
    if (logUsername == petUsername && logPassword == petPassword){
        pilih2 = menuPetugas();
        enum option{KELOLABUKU = 1, DAFTARPEMINJAMAN, DAFTARPENGEMBALIAN, KELUAR};
        while (pilih2 != KELUAR){
            switch (pilih2){
                case KELOLABUKU: {
                    KELOLA_BUKU:
                    int input;
                    string line;
                    ifstream file("data_buku.txt");
                    string judul, pengarang, kodeBuku, status;
                    system("cls");
                    cout << "                  Tabel Buku                  "<< endl; 
                    cout << "=============================================="<< endl; 
                    cout << "Judul Buku\t" << "Pengarang\t"<< "Kode\t" << "Status" << endl; 
                    cout << "=============================================="<< endl; 
                    while(getline(file, line)){
                        stringstream ss(line);
                        getline(ss, judul, ',');
                        getline(ss, pengarang, ',');
                        getline(ss, kodeBuku, ',');
                        getline(ss, status, ',');
                        cout << judul << " " << pengarang << " " << kodeBuku << " " << status << endl;
                    }
                    file.close();
                    cout << "\n "<< endl;
                    cout << "[1] Tambah Buku" << endl;
                    cout << "[2] Hapus Buku" << endl;
                    cout << "Masukkan pilihan: ";
                    cin >> input;
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    switch (input)
                    {
                    case 1:
                        {
                            // CASE TAMBAH BUKU :)
                            buku bk;
                            system("cls");
                            // input data
                            cout << "Masukkan judul buku: ";
                            getline(cin, bk.judul);
                            cout << "Masukkan nama pengarang: ";
                            getline(cin, bk.pengarang);
                            cout << "Masukkan kode buku: ";
                            getline(cin, bk.kode);
                            bk.status = "tersedia";

                            ofstream FileBuku;
                            FileBuku.open("data_buku.txt", ios::app);
                            FileBuku << bk.judul;
                            FileBuku << ",";
                            FileBuku << bk.pengarang;
                            FileBuku << ",";
                            FileBuku << bk.kode;
                            FileBuku << ",";
                            FileBuku << bk.status << endl;
                            FileBuku.close();
                            cout << "Buku berhasil ditambah" << endl;
                            system("pause");
                            goto KELOLA_BUKU;
                        }
                        break;
                    case 2:
                        {
                            // CASE HAPUS BUKU :)
                            string buku, pengarang, kodeBuku, status, line, inputKode;
                            int hapus;
                            cout << "Masukkan kode buku: ";
                            cin >> inputKode;

                            ifstream buku_data;
                            buku_data.open("data_buku.txt");
                            while (!buku_data.eof())
                            {
                                getline(buku_data, line);
                                stringstream ss(line);
                                getline(ss, buku, ',');
                                getline(ss, pengarang, ',');
                                getline(ss, kodeBuku, ',');
                                getline(ss, status, ',');
                                
                                if (inputKode == kodeBuku){
                                    fstream read_file;
                                read_file.open("data_buku.txt");
                                vector<string> lines;
                                string line;

                                while(getline(read_file, line)){
                                    lines.push_back(line);
                                }
                                read_file.close();
                                int line_number = 0;
                                for (int i = 0; i < lines.size(); i++){
                                    if (lines[i] == buku + "," + pengarang + "," + kodeBuku + "," + status){
                                        line_number = i;
                                    };
                                }
                                buku_data.close();
                                ofstream write_file;
                                write_file.open("data_buku.txt");
                                for (int i = 0; i < lines.size(); i++)
                                {
                                    if (i != line_number){
                                        write_file << lines[i] <<endl;
                                        hapus = 1;
                                    }
                                }
                                write_file.close();
                                }
                            }
                            if(hapus == 1){
                                cout << "Data Berhasil Dihapus" << endl;
                                system("pause");
                                goto KELOLA_BUKU;
                            }
                        }
                        break;
                    default:
                        break;
                    }
                }
                break;
                default:
                    break;
                }
        }
        if(pilih2 == KELUAR){
            cout << "Terima kasih dan sampai jumpa!" << endl;
            system("pause");
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
            cin.get();
            return 0;
        }
    } else {
        pilih2 = menuMahasiswa();
        enum option{DAFTARBUKU = 1, BUKU, PEMINJAMAN, PENGEMBALIAN, DAFTARPENGEMBALIAN, KELUAR};
        // ANCHOR Perubahan buku manual menjadi database
        while(pilih2 != KELUAR){
            switch (pilih2)
            {
            case DAFTARBUKU:
                daftarBuku();
                system("pause");
                goto label_pilih;
                break;
            case BUKU: {
                int book_pilih = menuBuku();
                while(book_pilih != 0 && book_pilih != 99){
                    int this_book = book_pilih;
                    ofstream filePeminjaman;
                    ifstream buku_data;
                    string buku, pengarang, kodeBuku, status, line, idPeminjam;
                    if (book_pilih == this_book)
                    {
                        int i = 0;
                        filePeminjaman.open("data_peminjaman.txt", ios::app);
                        buku_data.open("data_buku.txt");
                        while (!buku_data.eof())
                        {
                            getline(buku_data, line);
                            stringstream ss(line);
                            getline(ss, buku, ',');
                            getline(ss, pengarang, ',');
                            getline(ss, kodeBuku, ',');
                            getline(ss, status, ',');
                            getline(ss, idPeminjam, ',');
                            
                            if (i == this_book - 1)
                            {
                                fstream read_file;
                                read_file.open("data_buku.txt");
                                vector<string> lines;
                                string line;

                                while(getline(read_file, line)){
                                    lines.push_back(line);
                                }
                                read_file.close();
                                int line_number = 0;
                                for (int i = 0; i < lines.size(); i++){
                                    if (lines[i] == buku + "," + pengarang + "," + kodeBuku + "," + status + "," + idPeminjam){
                                        line_number = i;
                                    };
                                }
                                ofstream write_file;
                                write_file.open("data_buku.txt");
                                for (int i = 0; i < lines.size(); i++)
                                {
                                    if (i != line_number){
                                        write_file << lines[i] <<endl;
                                    } else {
                                        if (status == "kosong") {
                                            write_file << buku + "," + pengarang + "," + kodeBuku + "," + "kosong" + "," + idPeminjam << endl;
                                        } else if (status == "tersedia"){
                                            write_file << buku + "," + pengarang + "," + kodeBuku + "," + "kosong" + "," + logUsername << endl;
                                        }
                                    }
                                }
                                write_file.close();
                                if (status == "kosong"){
                                    cout << "Buku sedang dipinjam" << endl;
                                } else if(status == "tersedia"){
                                    filePeminjaman << buku << ",";
                                    filePeminjaman << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << ",";
                                    filePeminjaman << dateNext[1] << " " << dateNext[0] << " " << dateNext[2] << ",";
                                    filePeminjaman << logUsername << endl;
                                    filePeminjaman.close();
                                    cout << "Anda telah meminjam buku " << buku << " | " << pengarang << "." << endl;
                                    buku_data.close();
                                    cout << "Tanggal Peminjaman: " << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << endl;
                                }
                                system("pause");
                                goto label_pilih;
                            } 
                            i++;
                        }
                        cout << "Buku tidak ditemukan"<< endl;
                        system("pause");
                        goto label_pilih;
                    }
                }
                if (book_pilih == 0){
                    
                    ifstream buku_data;
                    buku_data.open("data_buku.txt");
                    string buku, pengarang ,kodeBuku, status, line, idPeminjam;
                    int i = 0, j = 0;
                    string kotak_judulBuku[10], kotak_idBuku[10], kotak_pengarang[10], kotak_status[10], kotak_idPeminjam[10];

                    while (getline(buku_data, line))
                    {
                        stringstream ss(line);
                        getline(ss, buku, ',');
                        getline(ss, pengarang, ',');
                        getline(ss, kodeBuku, ',');
                        getline(ss, status, ',');
                        getline(ss, idPeminjam, ',');
                        kotak_judulBuku[i] = buku;
                        kotak_idBuku[i] = kodeBuku;
                        kotak_pengarang[i] = pengarang;
                        kotak_status[i] = status;
                        kotak_idPeminjam[i] = idPeminjam;

                        i++;
                    }
                    buku_data.close();

                    string searchBuku;
                    int k = 0, pilih;

                    cin.clear();
                    cin.sync();
                    system("cls");
                    cout << "Ketik judul atau kode buku yang dicari"<< endl;
                    cout << "==================="<< endl;
                    cout << "Masukan kata kunci : "; 
                    getline(cin, searchBuku);
                    for (int k = 0; k <= i; k++){
                        if (kotak_judulBuku[k] == searchBuku || kotak_idBuku[k] == searchBuku)
                        {
                            fstream read_file;
                            read_file.open("data_buku.txt");
                            vector<string> lines;
                            string line;

                            while(getline(read_file, line)){
                                lines.push_back(line);
                            }
                            read_file.close();
                            int line_number = 0;
                            for (int i = 0; i < lines.size(); i++){
                                if (lines[i] == kotak_judulBuku[k] + "," + kotak_pengarang[k] + "," + kotak_idBuku[k] + "," + kotak_status[k] + "," + kotak_idPeminjam[k]){
                                    line_number = i;
                                };
                            }
                            ofstream write_file;
                            write_file.open("data_buku.txt");
                            for (int i = 0; i < lines.size(); i++)
                            {
                                if (i != line_number){
                                    write_file << lines[i] <<endl;
                                } else {
                                    if (status == "kosong")
                                    {
                                        write_file << kotak_judulBuku[k] + "," + kotak_pengarang[k] + "," + kotak_idBuku[k] + "," + "kosong" + "," + kotak_idPeminjam[k] << endl;
                                    }
                                    else if (status == "tersedia")
                                    {
                                        write_file << kotak_judulBuku[k] + "," + kotak_pengarang[k] + "," + kotak_idBuku[k] + "," + "kosong" + "," + logUsername << endl;
                                    }
                                }
                            }
                            write_file.close();
                            cout << "Buku " << kotak_judulBuku[k] << " ditemukan" << endl;
                            if (kotak_status[k] == "kosong")
                            {
                                cout << "Buku " << kotak_judulBuku[k] << " sedang dipinjam" << endl;
                                system("pause");
                                goto label_pilih;
                            } else {
                                // cout << "Apakah anda ingin meminjam buku tersebut (1/0)? ";
                                // cin >> pilih;
                                // if (pilih == 1)
                                // {
                                ofstream filePeminjaman;
                                filePeminjaman.open("data_peminjaman.txt", ios::app);
                                filePeminjaman << kotak_judulBuku[k] << ",";
                                filePeminjaman << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << ",";
                                filePeminjaman << logUsername << endl;
                                filePeminjaman.close();
                                cout << "Anda telah meminjam buku " << kotak_judulBuku[k] << " | " << kotak_idBuku[k] << "." << endl;
                                cout << "Tanggal Peminjaman: " << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << endl;
                                filePeminjaman.close();
                                system("pause");
                                goto label_pilih;
                                // }
                                // else
                                // {
                                // system("pause");
                                // goto label_pilih;
                                // }
                            }
                        }
                        else {
                            
                        }
                    }
                    cout << "Buku tidak ditemukan"<<endl;
                    system("pause");
                    goto label_pilih;
                } 
                goto label_pilih;               
            }break;
            
            case PEMINJAMAN: {
                string userNow;
                ifstream dataUser("data_mahasiswa.txt");
                while(!dataUser.eof()){
                    getline(dataUser, line);
                    stringstream ss(line);
                    getline(ss, username, ',');
                    getline(ss, password, ',');
                    getline(ss, nama, ',');
                    if (logUsername == username)
                    {
                        userNow = username;
                    }
                }
                string line;
                ifstream file("data_peminjaman.txt");
                string judul, tanggal_peminjaman, peminjam, tanggal_setKembali;
                system("cls");
                cout << "Tabel Peminjaman"<< endl; 
                cout << "=========================================="<< endl; 
                cout << "Judul Buku\t\t" << "Tanggal Peminjaman"<< endl; 
                cout << "=========================================="<< endl; 
                while(getline(file, line)){
                    stringstream ss(line);
                    getline(ss, judul, ',');
                    getline(ss, tanggal_peminjaman, ',');
                    getline(ss, tanggal_setKembali, ',');
                    getline(ss, peminjam, ',');

                    if (peminjam == userNow)
                    {
                        cout << judul << " " << tanggal_peminjaman << " " << peminjam << endl;
                    }
                }
                file.close();
                cout << endl;
                system("pause");
                goto label_pilih;
            }break; 
            
            case PENGEMBALIAN: {
                ofstream filePengembalian;
                string buku, pengarang ,line, idBuku, status, idPeminjam;
                filePengembalian.open("data_pengembalian.txt", ios::app);
                ifstream buku_data;

                string kode_buku;
                cout << "Ketik kode buku yang dikembalikan : ";
                cin>> kode_buku;

                buku_data.open("data_buku.txt");
                int i = 0;
                while (!buku_data.eof())
                {
                    getline(buku_data, line);
                    stringstream ss(line);
                    getline(ss, buku, ',');
                    getline(ss, pengarang, ',');
                    getline(ss, idBuku, ',');
                    getline(ss, status, ',');
                    getline(ss, idPeminjam, ',');
                    if (kode_buku == idBuku)
                    {
                        fstream read_file;
                        read_file.open("data_buku.txt");
                        vector<string> lines;
                        string line;

                        while(getline(read_file, line)){
                            lines.push_back(line);
                        }
                        read_file.close();
                        int line_number = 0;
                        for (int i = 0; i < lines.size(); i++){
                            if (lines[i] == buku + "," + pengarang + "," + idBuku + "," + status + "," + idPeminjam){
                                line_number = i;
                            };
                        }
                        ofstream write_file;
                        write_file.open("data_buku.txt");
                        for (int i = 0; i < lines.size(); i++)
                        {
                            if (i != line_number){
                                write_file << lines[i] <<endl;
                            } else {
                                if (logUsername == idPeminjam && status == "kosong") {
                                    write_file << buku + "," + pengarang + "," + idBuku + "," + "tersedia" + "," + "null" << endl;
                                } else if (logUsername != idPeminjam && status == "tersedia") {
                                    write_file << buku + "," + pengarang + "," + idBuku + "," + "tersedia" + "," + idPeminjam << endl;
                                } else if (logUsername != idPeminjam && status == "kosong") {
                                    write_file << buku + "," + pengarang + "," + idBuku + "," + "kosong" + "," + idPeminjam << endl;
                                } else if (logUsername == idPeminjam && status == "tersedia") {
                                    write_file << buku + "," + pengarang + "," + idBuku + "," + "terseida" + "," + "null" << endl;
                                }
                                
                            }
                        }
                        if (logUsername == idPeminjam)
                        {   
                            write_file.close();
                            // Memanggil tanggal peminjaman dari data_peminjaman.txt 
                            string judul, tanggal_peminjaman ,tanggal_set_kembali, peminjam, line;
                            string get_tanggal_set_kembali;
                            ifstream data_peminjaman;
                            data_peminjaman.open("data_peminjaman.txt");
                            int i = 0;
                            while (!data_peminjaman.eof())
                            {
                                getline(data_peminjaman, line);
                                stringstream ss(line);
                                getline(ss, judul, ',');
                                getline(ss, tanggal_peminjaman, ',');
                                getline(ss, tanggal_set_kembali, ',');
                                getline(ss, peminjam, ',');
                                if (logUsername == peminjam && judul == buku)
                                {
                                    get_tanggal_set_kembali = tanggal_set_kembali;
                                }
                            }
                            data_peminjaman.close();
                            // Memecah string tanggal peminjaman yang sudah diambil
                            string getHari, getTahun, getBulan;
                            stringstream ss(get_tanggal_set_kembali);
                            getline(ss, getHari, ' ');
                            getline(ss, getBulan, ' ');
                            getline(ss, getTahun, ' ');
                            // Memasukkan tanggal peminjaman ke array
                            stringstream temp;
                            temp << getHari;
                            temp >> dateNext[1];
                            temp << getBulan;
                            temp >> dateNext[0];
                            temp << getTahun;
                            temp >> dateNext[2];
                            
                            // HITUNG DENDA
                            int bulan = 0, hari = 0;
                            int denda = 0;
                            // Tahun > Bulan > Hari
                            if(dateNow[2] > dateNext[2]){
                                bulan = (dateNow[2] - dateNext[2])*12;
                                if (dateNow[0] > dateNext[0]){
                                    bulan += (dateNow[0] - dateNext[0]);
                                } else if(dateNow[0] < dateNext[0]){
                                    bulan -= (dateNext[0] - dateNow[0]);
                                }
                                hari = bulan * 30;
                                if (dateNow[1] > dateNext[1]){
                                    hari += dateNow[1] - dateNext[1];
                                } else if(dateNow[1] < dateNext[1]){
                                    hari -= dateNext[1] - dateNow[1];
                                }
                                denda = hari * 500;
                            } else if(dateNow[0] > dateNext[0]){
                                // Bulan > Hari
                                hari = (dateNow[0] - dateNext[0])*30;
                                if (dateNow[1] > dateNext[1]){
                                    hari += dateNow[1] - dateNext[1];
                                } else if(dateNow[1] < dateNext[1]){
                                    hari -= dateNext[1] - dateNow[1];
                                }
                                denda = hari * 500;
                            } else if(dateNow[1] > dateNext[1]){
                                // Hari
                                denda = (dateNow[1] - dateNext[1]) * 500;
                            }
                            filePengembalian << buku << ",";
                            filePengembalian << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << ",";
                            filePengembalian << logUsername << endl;
                            filePengembalian.close();
                            cout << "Buku " << buku << " | " << pengarang << " Telah Dikembalikan." << endl;
                            buku_data.close();
                            cout << "Tanggal Pengembalian : " << dateNow[1] << " " << dateNow[0] << " " << dateNow[2] << endl;
                            
                            if(denda != 0){
                                cout << endl;
                                cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                                cout << "Terlambat mengembalikan!" << endl;
                                cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                                cout << "Anda memiliki denda: " << denda << endl;
                            }
                            system("pause");
                            goto label_pilih;
                        } else {
                            cout << "Anda tidak punya buku ini" << endl;
                            system("pause");
                            goto label_pilih;
                        }
                    }
                    i++;
                }
                cout << "Buku tidak ditemukan" << endl;
                system("pause");
                goto label_pilih;
            }break; 

            case DAFTARPENGEMBALIAN: {
                string userNow;
                ifstream dataUser("data_mahasiswa.txt");
                while(!dataUser.eof()){
                    getline(dataUser, line);
                    stringstream ss(line);
                    getline(ss, username, ',');
                    getline(ss, password, ',');
                    getline(ss, nama, ',');
                    if (logUsername == username)
                    {
                        userNow = username;
                    }
                }

                string line;
                ifstream file("data_pengembalian.txt");
                string judul, tanggal_pengembalian, pengembali;
                system("cls");
                cout << "Tabel Pengembalian"<< endl; 
                cout << "=========================================="<< endl; 
                cout << "Judul Buku\t\t" << "Tanggal pengembalian"<< endl; 
                cout << "=========================================="<< endl; 
                while(getline(file, line)){
                    stringstream ss(line);
                    getline(ss, judul, ',');
                    getline(ss, tanggal_pengembalian, ',');
                    getline(ss, pengembali, ',');
                    if (pengembali == userNow)
                    {
                        cout << judul << " " << tanggal_pengembalian << endl;
                    }
                }
                file.close();
                cout << endl;
                system("pause");
                goto label_pilih;
            }break; 
            
            default:
                cout << "Masukkan pilihan yang benar" << endl;
                system("pause");
                goto label_pilih;
                break;
            }
        }
        if(pilih2 == KELUAR){
            cout << "Terima kasih dan sampai jumpa!" << endl;
            system("pause");
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
            cin.get();
            return 0;
        }

    }
}

void login(){
    mahasiswa mhs;
    int count = 0;
    cout << "====================" << endl;
    cout << "Welcome!" << endl;
    cout << "====================" << endl;
    cout << "Username: ";
    cin >> logUsername;
    cout << "Password: ";
    cin >> logPassword;

    if(logUsername == petUsername && logPassword == petPassword){
        count = 1;
        system("cls");
        cout << "\nLogin berhasil!" << endl;
        cout << "\nAnda Login Sebagai Admin" << endl;
        system("pause");
    } else {
        ifstream input("data_mahasiswa.txt");
        while(!input.eof()){
            getline(input, line);
            stringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password, ',');
            getline(ss, nama, ',');
            if (username == logUsername && password == logPassword)
            {
                count = 1;
                system("cls");
                cout << "\nLogin berhasil!" << endl;
                cout << "\nAnda Login Sebagai Mahasiswa" << endl;
                system("pause");
                input.close();
            }
        }
    }
    if (count != 1){        
        cout << "\nLogin anda salah, coba lagi!" << endl;
        system("pause");
        main();
    }
}
void registrasi(){
    mahasiswa mhs;
    // input data
    cout << "Masukkan nama: ";
    getline(cin, mhs.nama);
    cout << "Masukkan NIM: ";
    getline(cin, mhs.NIM);
    cout << "Masukkan Password: ";
    getline(cin, mhs.password);

    ofstream fileRegister;
    fileRegister.open("data_mahasiswa.txt", ios::app);
    fileRegister << "\n";
    fileRegister << mhs.NIM;
    fileRegister << ",";
    fileRegister << mhs.password;
    fileRegister << ",";
    fileRegister << mhs.nama;
    fileRegister.close();
    main();
}
int menu(){
    int pilih = 0;
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan" << endl;
    cout << "=======================" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu (1-3): ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return pilih;
}
int menuPetugas(){
    int pilih;
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan | " << petUsername << endl;
    cout << "=======================" << endl;
    cout << "1. Kelola Buku" << endl;
    cout << "2. Daftar Peminjaman" << endl;
    cout << "3. Daftar Pengembalian" << endl;
    cout << "4. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}
int menuMahasiswa(){
    int pilih;
    mahasiswa mhs;
    string userNow;
    ifstream dataUser("data_mahasiswa.txt");
    while (!dataUser.eof())
    {
        getline(dataUser, line);
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, nama, ',');
        if (logUsername == username)
        {
            mhs.NIM = logUsername;
            mhs.nama = nama;
        }
    }
    system("cls");
    cout << "=======================" << endl;
    cout << "Aplikasi Perpustakaan | " << mhs.nama << endl;
    cout << "=======================" << endl;
    cout << "1. Daftar Buku Anda" << endl;
    cout << "2. Peminjaman" << endl;
    cout << "3. Daftar Peminjaman" << endl;
    cout << "4. Pengembalian" << endl;
    cout << "5. Daftar Pengembalian" << endl;
    cout << "6. Keluar" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}
int menuBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "=======================" << endl;
    cout << "Pilih Buku" << endl;
    cout << "=======================" << endl;
    cout << "0. Cari Buku" << endl;
    cout << "99. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "List Buku" << endl;
    cout << "=======================" << endl;

    ifstream listBuku;
    listBuku.open("data_buku.txt");
    string listJudulBuku, listLineBuku;
    int listNo = 1;

    while (getline(listBuku,listLineBuku))
    {
        stringstream ss(listLineBuku);
        getline(ss, listJudulBuku, ',');
        cout << listNo << ". " << listJudulBuku << endl;
        listNo++;
    }
    listBuku.close();
    // cout << "1. Your Name" << endl;
    // cout << "2. Weathering With You" << endl;
    // cout << "3. Re:ZERO" << endl;
    cout << "=======================" << endl;
    cout << "Pilih menu: ";
    cin >> pilih;
    return pilih;
}

int daftarBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "=======================" << endl;
    cout << "Perpustakaan Anda" << endl;
    cout << "=======================" << endl;
    cout << "99. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    cout << "List Buku" << endl;
    cout << "=======================" << endl;

    ifstream listBuku;
    listBuku.open("data_buku.txt");
    string listJudulBuku, listLineBuku, listPengarang, listIdBuku, listStatus, listIdPeminjam;
    int listNo = 1;

    while (getline(listBuku,listLineBuku))
    {
        stringstream ss(listLineBuku);
        getline(ss, listJudulBuku, ',');
        getline(ss, listPengarang, ',');
        getline(ss, listIdBuku, ',');
        getline(ss, listStatus, ',');
        getline(ss, listIdPeminjam, ',');
        
        if (listIdPeminjam == logUsername)
        {
            cout << listNo << ". " << listJudulBuku << " | " << listIdPeminjam << "\n" <<endl;
            listNo++;
        }
        
    }
    listBuku.close();
}
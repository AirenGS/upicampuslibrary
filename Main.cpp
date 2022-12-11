#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <cstring>  
#include <limits>
#include <stdio.h>
#include <vector>
#include <iomanip>
#include <windows.h>

using namespace std;
struct buku{
    string judul, pengarang, kode, status, peminjam; 
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
int tanggalMaker();
void warna(unsigned short warna);

// Global
int menu();
void login();
void registrasi();
// Petugas
int menuPetugas();
int kelolaBuku();
void tambahBuku();
int hapusBuku();
// Mahasiswa
int menuMahasiswa();
int menuBuku();
int daftarBuku();
int pinjamBuku(int inputBuku, int thisBuku);
int cariBuku();
void daftarPeminjaman();
int pengembalianBuku();
void daftarPengembalian();

int main()
{
    HOME:
    system("cls");
    int pilih = menu();
    tanggalMaker();
    // MENU AWAL
    switch (pilih)
    {
    case 1:
        // REGISTRASI
        system ("cls");
        registrasi();
        system ("cls");
        break;
    case 2: 
        // LOGIN
        system ("cls");
        login();
        system ("cls");
        break;
    case 3:
        // KELUAR
        warna(2);
        cout << "Terima kasih dan sampai jumpa!";
        exit(0);
    default:
        {   
            warna(4);
            cout << "Masukan pilihan yang valid" << endl;
            warna(7);
            system("pause");
            main();
            break;
        }
    }
    label_pilih:
    int pilih2;
    if (logUsername == petUsername && logPassword == petPassword){
        pilih2 = menuPetugas();
        enum option{KELOLABUKU = 1, KELUAR};
        while (pilih2 != KELUAR){
            switch (pilih2){
                case KELOLABUKU: {
                    int back = kelolaBuku();
                    if(back == 1){
                        goto label_pilih;
                    }
                }
                break;
                default:
                    break;
                }
        }
        if(pilih2 == KELUAR){
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
        }
    } else {
        pilih2 = menuMahasiswa();
        enum option{DAFTARBUKU = 1, BUKU, PEMINJAMAN, PENGEMBALIAN, DAFTARPENGEMBALIAN, KELUAR};
        while(pilih2 != KELUAR){
            switch (pilih2)
            {
            case DAFTARBUKU:
                daftarBuku();
                system("pause");
                goto label_pilih;
                break;
            case BUKU: {
                BUKU:
                int back;
                int book_pilih = menuBuku();
                while(book_pilih != 0 && book_pilih != 99){
                int this_book = book_pilih;
                int back = pinjamBuku(book_pilih, this_book);
                if(back = 1){
                    goto BUKU;
                } 
                }
                if (book_pilih == 0){
                    int back = cariBuku();
                    if(back==1){
                        goto BUKU;
                    }
                    system("pause");
                }
                goto label_pilih;               
            }break;
            
            case PEMINJAMAN: {
                daftarPeminjaman();
                cout << endl;
                system("pause");
                goto label_pilih;
            }break; 
            
            case PENGEMBALIAN: {
                int back = pengembalianBuku();
                system("pause");
                goto label_pilih;
            }break; 

            case DAFTARPENGEMBALIAN: {
                daftarPengembalian();
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
            string *logUsername = NULL;
            string *logPassword = NULL;
            string *nama = NULL;
            system("cls");
            goto HOME;
        }

    }
}
void warna(unsigned short warna){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, warna);
}
int tanggalMaker(){
    int i = 0;
    // ANCHOR Kostum tanggal disini
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
}
void login(){
    mahasiswa mhs;
    int count = 0;
    warna(1);
    cout << "\t\t\t\t\t============================" << endl;
    warna(5);
    cout << "\t\t\t\t\t\tMENU LOGIN" << endl;
    warna(1);
    cout << "\t\t\t\t\t============================\n" << endl;
    warna(5);
    cout << "Username (Masukan NIM sebagai username)\t: ";
    warna(7);
    cin >> logUsername;
    warna(5);
    cout << "Password\t\t\t\t: ";
    warna(7);
    cin >> logPassword;

    if(logUsername == petUsername && logPassword == petPassword){
        count = 1;
        system("cls");
        warna(2);
        cout << "\nLogin berhasil!" << endl;
        cout << "\nAnda Login Sebagai Admin" << endl;
        warna(7);
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
                warna(2);
                cout << "\nLogin berhasil!" << endl;
                cout << "\nAnda Login Sebagai Mahasiswa" << endl;
                warna(7);
                system("pause");
                input.close();
            }
        }
    }
    if (count != 1){        
        warna(4);
        cout << "\nLogin anda salah, coba lagi!" << endl;
        warna(7);
        system("pause");
        main();
    }
}
void registrasi(){
    mahasiswa mhs;
    // input data
    warna(1);
    cout << "\t\t\t\t\t================================" << endl;
    warna(5);
    cout << "\t\t\t\t\t\tMENU REGISTRASI" << endl;
    warna(1);
    cout << "\t\t\t\t\t================================\n" << endl;
    warna(5);
    cout << "Nama Lengkap\t\t\t: ";
    warna(7);
    getline(cin, mhs.nama);
    warna(5);
    cout << "Nomor Induk Mahasiswa (NIM)\t: ";
    warna(7);
    getline(cin, mhs.NIM);
    warna(5);
    cout << "Buat Password Baru\t\t: ";
    warna(7);
    getline(cin, mhs.password);
    
    ifstream input("data_mahasiswa.txt");

    while(!input.eof()){
        getline(input, line);
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, nama, ',');

        if (username == mhs.NIM)
        {
            system("cls");
            cout << "NIM Sudah Dipakai!" << endl;
            system("pause");
            main();
        }

    }
    
    if (mhs.NIM.length() != 7)
    {
        system("cls");
        cout << "NIM Harus 7 Digit!" << endl;
        system("pause");
        main();
    }

    ofstream fileRegister;
    fileRegister.open("data_mahasiswa.txt", ios::app);
    fileRegister << "\n";
    fileRegister << mhs.NIM;
    fileRegister << ",";
    fileRegister << mhs.password;
    fileRegister << ",";
    fileRegister << mhs.nama;
    fileRegister.close();

    system("cls");
    warna(2);
    cout << "\nRegister berhasil!" << endl;
    warna(7);
    system("pause");
    main();
}
int menu(){
    int pilih = 0;
    system("cls");
    warna(1);
    cout << "\t\t\t\t\t==================================" << endl;
    warna(7);
    warna(5);
    cout << "\t\t\t\t\t\tUPI CAMPUS LIBRARY" << endl;
    warna(1);
    cout << "\t\t\t\t\t==================================\n\n" << endl;
    warna(5);
    cout << "[1] REGISTER" << endl;
    cout << "[2] LOGIN" << endl;
    cout << "[3] KELUAR\n" << endl;
    warna(7);
    cout << "Silahkan pilih menu\t: ";
    cin >> pilih;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    return pilih;
}
int menuPetugas(){
    int pilih;
    system("cls");
    warna(7);
    cout << "\t\t\t\t\t==================================" << endl;
    warna(6);
    cout << "\t\t\t\t\t\t  W E L C O M E                       - "<< petUsername << endl;
    cout << "\t\t\t\t\t\tUPI CAMPUS LIBRARY" << endl;
    warna(7);
    cout << "\t\t\t\t\t==================================\n\n" << endl;
    warna(6);
    cout << "[1] Kelola Buku" << endl;
    cout << "[2] Keluar" << endl;
    cout << "Silahkan pilih menu\t: ";
    cin >> pilih;
    return pilih;
}
int kelolaBuku(){
    KELOLA_BUKU:
    int back = 1;
    int input;
    string line;
    ifstream file("data_buku.txt");
    string judul, pengarang, kodeBuku, status;
    system("cls");
    cout << "                              Tabel Buku                               "<< endl; 
    cout << "======================================================================="<< endl; 
    cout << "| Judul Buku             | Pengarang         | Kode Buku   | Status   |"<< endl; 
    cout << "======================================================================="<< endl; 
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, judul, ',');
        getline(ss, pengarang, ',');
        getline(ss, kodeBuku, ',');
        getline(ss, status, ',');
        // cout << judul << " " << pengarang << " " << kodeBuku << " " << status << endl;
        cout<<"| "<<setiosflags(ios::left)<<setw(23)<<judul<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(18)<<pengarang<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(12)<<kodeBuku<<"|";
        cout<<" "<<setiosflags(ios::left)<<setw(9)<<status<<"|"<< endl;
    }
    file.close();
    cout << "\n "<< endl;
    cout << "[1] Tambah Buku" << endl;
    cout << "[2] Hapus Buku" << endl;
    cout << "[3] Kembali ke menu petugas" << endl;
    cout << "Masukkan pilihan: ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    switch (input)
    {
    case 1: {
        // CASE TAMBAH BUKU
        tambahBuku();
        system("pause");
        goto KELOLA_BUKU;
    }
    break;
    case 2: {
        // CASE HAPUS BUKU :)
        int hapus = hapusBuku();
        if(hapus == 1){
            system("pause");
            goto KELOLA_BUKU;
        }
    } break;
    case 3: {
        return back;
    } break;
    default: {
        cout << "Masukkan pilihan yang benar" << endl;
        system("pause");
        goto KELOLA_BUKU;
    } break;
    }
}
void tambahBuku(){
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
    bk.peminjam = "null";

    ofstream FileBuku;
    FileBuku.open("data_buku.txt", ios::app);
    FileBuku << bk.judul;
    FileBuku << ",";
    FileBuku << bk.pengarang;
    FileBuku << ",";
    FileBuku << bk.kode;
    FileBuku << ",";
    FileBuku << bk.status;
    FileBuku << ",";
    FileBuku << bk.peminjam << endl;
    FileBuku.close();
    cout << "\n======================" << endl;
    cout << "Buku berhasil ditambah" << endl;
    cout << "======================" << endl;
}
int hapusBuku(){
    string buku, pengarang, kodeBuku, status, peminjam, line, inputKode;
    int hapus = 1;
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
        getline(ss, peminjam, ',');
        
        if (inputKode == kodeBuku){
            fstream read_file;
            read_file.open("data_buku.txt");
            vector<string> lines;
            string line;

            while(getline(read_file, line)){
                lines.push_back(line);
            }
            read_file.close();
            int line_number;
            for (int i = 0; i < lines.size(); i++){
                if (lines[i] == buku + "," + pengarang + "," + kodeBuku + "," + status + "," + peminjam){
                    line_number = i;
                };
            }
            buku_data.close();
            ofstream write_file;
            write_file.open("data_buku.txt");
            for (int i = 0; i < lines.size(); i++){
                if (i != line_number){
                    write_file << lines[i] <<endl;
                }
            }
            cout << "Data Berhasil Dihapus" << endl;
            write_file.close();
            return hapus;
        }
    }
    cout << "Buku tidak ditemukan" << endl;
    return hapus;
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
    warna(7);
    cout << "\t\t\t\t\t==================================" << endl;
    warna(6);
    cout << "\t\t\t\t\t\t  W E L C O M E                       - "<< mhs.nama << endl;
    cout << "\t\t\t\t\t\tUPI CAMPUS LIBRARY" << endl;
    warna(7);
    cout << "\t\t\t\t\t==================================\n\n" << endl;
    warna(6);
    cout << "[1] Daftar Buku Anda" << endl;
    cout << "[2] Peminjaman" << endl;
    cout << "[3] Daftar Peminjaman" << endl;
    cout << "[4] Pengembalian" << endl;
    cout << "[5] Daftar Pengembalian" << endl;
    cout << "[6] Keluar\n" << endl;
    warna(6);
    cout << "Silahkan pilih menu\t: ";
    warna(7);
    cin >> pilih;
    return pilih;
}
int menuBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "\t\t\t\t\t============================" << endl;
    warna(5);
    cout << "\t\t\t\t\t\tPilih Buku" << endl;
    warna(7);
    cout << "\t\t\t\t\t============================\n\n" << endl;
    cout << "0. Cari Buku" << endl;
    cout << "99. Kembali ke laman utama" << endl;
    cout << "=======================" << endl;
    warna(5);
    cout << "List Buku" << endl;
    warna(7);
    cout << "=======================" << endl;

    ifstream listBuku;
    listBuku.open("data_buku.txt");
    string listJudulBuku, listLineBuku, listPengarang, listIdBuku, listStatusBuku;
    int listNo = 1;
    string tandaBuku[2];
    tandaBuku[0] = " " ;
    tandaBuku[1] = "Kosong";

    while (getline(listBuku,listLineBuku))
    {
        stringstream ss(listLineBuku);
        getline(ss, listJudulBuku, ',');
        getline(ss, listPengarang, ',');
        getline(ss, listIdBuku, ',');
        getline(ss, listStatusBuku, ',');
        if (listStatusBuku == "kosong") {
            cout << listNo << ". " << listJudulBuku << " [" << tandaBuku[1]<< "] " << endl;
        } else {
            cout << listNo << ". " << listJudulBuku << " " << tandaBuku[0]<< endl;
        }
        
        listNo++;
    }
    listBuku.close();
    cout << "=======================\n" << endl;
    cout << "Silahkan pilih menu\t: ";
    cin >> pilih;
    return pilih;
}
int daftarBuku(){
    int pilih;
    system("cls");
    //manual
    cout << "\t\t\t\t\t===============================" << endl;
    warna(5);
    cout << "\t\t\t\t\t\tPERPUSTAKAAN ANDA" << endl;
    warna(7);
    cout << "\t\t\t\t\t===============================\n\n\n" << endl;
    cout << "=======================" << endl;
    warna(5);
    cout << "      List Buku" << endl;
    warna(7);
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
int pinjamBuku(int inputBuku, int thisBuku){
    int back = 1;
    string buku, pengarang, kodeBuku, status, line, idPeminjam;
    ofstream filePeminjaman;
    ifstream buku_data;
    if (inputBuku == thisBuku)
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
            
            if (i == thisBuku - 1)
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
                return back;
            } 
            i++;
        }
        cout << "Buku tidak ditemukan"<< endl;
        system("pause");
        return back;
    }
}
int cariBuku(){
    string buku, pengarang ,kodeBuku, status, line, idPeminjam;
    int i = 0, j = 0;
    int back = 1;
    string kotak_judulBuku[10], kotak_idBuku[10], kotak_pengarang[10], kotak_status[10], kotak_idPeminjam[10];
    ifstream buku_data;
    buku_data.open("data_buku.txt");

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
                return back;
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
                return back;
                // }
                // else
                // {
                // system("pause");
                // goto label_pilih;
                // }
            }
        }
    }
    cout << "Buku tidak ditemukan"<<endl;
    system("pause");
    return back;
}
void daftarPeminjaman(){
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
    cout << "================================================================================================="<< endl; 
    cout << "|Judul Buku              |Tanggal Peminjaman          |Tanggal Kembali             |Peminjam    |"<< endl; 
    cout << "================================================================================================="<< endl; 
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, judul, ',');
        getline(ss, tanggal_peminjaman, ',');
        getline(ss, tanggal_setKembali, ',');
        getline(ss, peminjam, ',');

        if (peminjam == userNow)
        {
            // cout << judul << " " << tanggal_peminjaman << " " << peminjam << endl;
            cout<<"| "<<setiosflags(ios::left)<<setw(23)<<judul<<"|";
            cout<<" "<<setiosflags(ios::left)<<setw(27)<<tanggal_peminjaman<<"|";
            cout<<" "<<setiosflags(ios::left)<<setw(27)<<tanggal_setKembali<<"|";
            cout<<" "<<setiosflags(ios::left)<<setw(11)<<peminjam<<"|"<<endl;
        }
    }
    file.close();
}
int pengembalianBuku(){
    string buku, pengarang ,line, idBuku, status, idPeminjam;
    int back = 1;
    ofstream filePengembalian;
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
                        write_file << buku + "," + pengarang + "," + idBuku + "," + "tersedia" + "," + "null" << endl;
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
                return back;
            } else {
                cout << "Anda tidak punya buku ini" << endl;
                return back;
            }
        }
        i++;
    }
    cout << "Buku tidak ditemukan" << endl;
    return back;
}
void daftarPengembalian(){
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
    cout << "========================================================="<< endl; 
    cout << "|Judul Buku              |Tanggal Pengembalian          |"<< endl; 
    cout << "========================================================="<< endl; 
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, judul, ',');
        getline(ss, tanggal_pengembalian, ',');
        getline(ss, pengembali, ',');

        if (pengembali == userNow)
        {
            // cout << judul << " " << tanggal_pengembalian << endl;
            cout<<"| "<<setiosflags(ios::left)<<setw(23)<<judul<<"|";
            cout<<" "<<setiosflags(ios::left)<<setw(29)<<tanggal_pengembalian<<"|"<<endl;
        }
    }
    file.close();
}
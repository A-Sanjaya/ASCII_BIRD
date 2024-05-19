namespace tampilan {

  void Clear(); //menghapus karakter di terminal
               
  class Layar {
    /* Gambaran tampilan layar */

    //y y=0
    //|
    //|
    //|
    //|
    //| x=0
    //------------------x

    //*Fungsi: media yang digunakan untuk menggambarkan objek-objek dalam game

    private:
      std::vector<std::string> kanvas; //-> 
      char background; //-> menentukan tampilan jika 
      int lebar; //-> lebar layar
      int tinggi; //-> tinggi layar
                  
    public:
      Layar(...); // -> membuat objek layar
      int CenterY(); // -> mencari koordinat tengah secara vertikal
      int CenterX(); // -> mencari koordinat tengah secara horizontal 
      int GetTinggi(); // -> mengembalikan nilai tinggi
      int GetLebar(); // -> mengembalikan nilai lebar
      void Clear(); // -> mengosongkan kanvas (mengubah semua karakter manjadi background)
      void print(); // -> menampilkan kanvas pada terminal
      void ganti(...); // -> mengganti karakter kanvas pada coordinat yang diberikan
  };
};

namespace Game {
  class Burung {

    //*Fungsi: menyimpan informasi mengenai objek burung
    
    private:
    char model; // -> karakter yang menggambarkan burung
    int tinggi_lompat; // -> tinggi lompatan
    int gravitasi; // -> pengurangan posisi y setiap fungis gravitasi dipanggil
    int x; // -> koordinat posisi horizontal burung
    int y; // -> koordinat posisi vertikal burung
    int score; // -> skor burung
    int score_inc; // -> penambahan score burung setiap berhasil melewati 1 pilar
 
    public:
    Burung(); // -> membuat objek burung
    int GetScore(); // -> mengembalikan nilai skor
    void AddScore(); // -> menambah skor sesuai score_inc
    int GetX(); // -> mengembalikan koordinat posisi horizontal burung
    int GetY(); // -> mengembalikan koordinat posisi vertikal burung
    void Lompat(); // -> melompat (menaikkan posisi burung ke atas sesuai tinggi_lompatan)
    void Gambar(...); // -> menggambar ascii pada kanvas layar yang diberikan
    void Gravitasi(...); // menurunan posisi burung sesuai gravitas
    void Die(); // mematikan burung (die = true)
    void IsDie(); // mematikan burung (die = true)
  };

  class Pilar {

    //*Fungsi: rintangan pada game

    private:
      char model; // -> karakter yang menggambarkan burung
      int tinggi; // -> tinggi pilar
      int x; // -> posisi horizontal pilar
      struct Gap {int y1; int y2;} gap; // -> area lubang pada pilar
    public:
      Pilar(...); // -> membaut objek pilar
      int GetX(); // -> mengembalikan nilai posisi horizontal pilar
      void SetX(...); // -> mengubah nilai x 
      void GenerateRandomLevel(...); // -> menentukan lubang pada pilar secara acak
      void Gambar(...); // -> menggambar pilar pada kanvas layar
      bool kena_burung(...); // -> cek tertabrakan dengan burung
      void MoveX(...); // -> memindahkan posisi horizontal pilar sesuai perpindahan yang diberikan
  };

  class Pilars {

    //*Fungsi: menampung beberapa pilar

    private:
    std::vector<Pilar> pilars; // -> berisi objek pilar-pilar
    int banyak_pilar; // -> banyak pilar yang ditampung
    int minimum_gap; // -> ukuran celah minimal di setiap pilar
    int movement; // -> perpindahan seluruh pilar
    Tampilan::Layar & layar; // -> layar yang akan digambarkan objek seluruh pilar


    public:
    Pilars(...); // -> membuat objek pilar
    void Move(...); // -> memindahkan seluruh pilar
    void GambarSemua(); // -> menggambar seluruh pilar ke kanvas layar
    bool kena_burung(...); // -> cek tabrakan antara burung dan pilar
  };

  void GameOver(...); // -> menu game over (menampilkan skor akhir)
};

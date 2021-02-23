## Pengenalan

Hibiscus Sense merupakan _Internet of Things (IoT)_ development board (buatan Malaysia) yang dikuasakan oleh mikropengawal popular yang tidak asing lagi dalam kalangan maker, iaitu ESP32. Hibiscus Sense bukan IoT development board, padanya terdapat 3 sensor dan 3 aktuator, yang sesuai untuk kita gunakan dalam tujuan pembelajaran:
- 3 sensor:
    - APDS9960 : sensor persekitaran, mengesan warna RGB (Merah, Hijau dan Biru), jarak dekat (proximity), isyarat arah pergerakan (jarak dekat). 
    - BME280 : sensor persekitaran, mengesan altitud, tekanan udara, kelembapan dan suhu.
    - MPU6050 : sensor gerakan 6-paksi, mengesan pecutan graviti 3-paksi, putaran 3-paksi dan suhu.
- 3 aktuator:
    - Buzzer Kecil: bunyi buzzer hanya dalam jarak dekat.
    - LED: LED berwarna biru.
    - LED RGB: WS2812 RGB LED.

Hibiscus Sense dilengkapi dengan port USB Type-C, bagi tujuan pengaktifan development board dan memprogramkan mikropengawal ESP32. Ia juga dilengkapi dengan pengubah protokol USB-kepada-Serial, Silicon Labs CP2104 dengan litar bootloader automatik, jadi kita tidak perlu menekan butang RESET setiap kali untuk memuat naik program.

Walaupun, kita dapat memprogram ESP32 menggunakan bahasa pengaturcaraan lain seperti C, C ++ dan Micropython, tetapi dalam tutorial ini kita akan menggunakan Arduino sebagai platform pembelajaran dan prototaip.


## Ciri-ciri Hibuscus Sense

- LED biru disambungkan ke ESP32's GPIO2.
- Buzzer Kecil disambungkan ke ESP32's GPIO13.
- WS2812 RGB LED disambungkan ke ESP32's GPIO16.
- Semua GPIO dapat menghasilkan input / output digital (3.3V) dan output isyarat PWM, kecuali GPIO34-GPIO39 kerana ia adalah pin input sahaja.
- ESP32 ini VSPIselesai miso GPIO19 , MOSI GPIO32 , CLK GPIO18 dan CS GPIO5 .
- ESP32's I2C SDA GPIO21 dan SCL GPIO22 , tanpa perintang penarik.
- Sensor : APDS9960 , BME280 dan MPU6050 interfaced kepada ESP32 ini I2C, alamat I2C sepatutunya 0x39, 0x77dan 0x68.
- Elakkan menggunakan saluran ADC2 semasa menggunakan WiFi.
- Setiap arus maksimum mutlak GPIO ditarik hanya 16mA.
- Pengukuran papan termasuk header dalam mm: 58.7 x 27 x 13.3 (panjang x lebar x tinggi).
- Pengukuran bungkusan dalam mm: 71.8 x 35.5 x 20.4 (panjang x lebar x tinggi).


## Penyediaan Bahan Pembelajaran

Sebelum memulakan pembelajaran untuk mengawal penggerak dan memperoleh data dari sensor pada Hibiscus Sense menggunakan alat dan bahasa pengaturcaraan Arduino, kita harus memastikan semua bahan pembelajaran sudah siap, seperti di bawah:

    1. Hibiscus Sense dan kabel USB Type-A hingga Type-C. Sekiranya anda belum memilikinya, anda boleh membelinya 🛒 Myduino
    2. Arduino IDE. Muat turun dari sini: Windows / Linux 32-bit , 64-bit , ARM 32-bit ARM 64-bit / Mac OSX .
    3. Library perkakasan ESP32 . Di bawah ini adalah tangkapan skrin, menunjukkan Arduino IDE Boards Manager(Menu IDE Arduino: Tools > Board:"_______" > Boards Manager... ) yang sudah mempunyai library perkakasan esp32 INSTALLED. Ikuti arahan ini untuk memasangnya.


## Memasukkan Hibiscus ke Port USB Komputer

Sambungkan kabel USB Type-C ke Hibiscus Sense dan Type-A ke komputer kita. Hibiscus Sense dilengkapi dengan program pratetap untuk menguji penggerak dan sensor on-board. Seharusnya sekarang kita akan melihat buzzer berdengung, LED RGB berubah warna, LED biru berkedip dan bacaan sensor di Serial Monitor (kita harus membuka Arduino IDE Serial Monitor untuk melihat data). Katakanlah, anda tidak melihat sebarang reaksi di papan tulis, anda boleh menghubungi Encik Ariffin melalui WhatsApp untuk mendapatkan bantuan.

## Latihan 1: Kawal LED Biru pada GPIO2 (Strobe Light Effect)

Terdapat 1x LED biru yang dilabel sebagai LEDon-board, seperti yang dilingkari pada gambar di atas. Litar LED ini adalah active-low circuit , seperti yang ditunjukkan dalam skema di bawah ini, yang terminal negatif (-ve) LED ini disambungkan ke GPIO2, oleh itu kita harus menarik keadaan GPIO2 ke keadaan LOW, untuk menyelesaikannya litar, maka lampu LED akan menyala. Jika tidak, dengan menarik keadaan GPIO2 ke HIGH, lampu LED akan mati.

Ini adalah tingkah laku yang jarang sekali, tetapi ada baiknya kita belajar bagaimana litar elektronik boleh berkelakuan baik. Manakala, reka bentuk litar biasa adalah active-high circuit , di mana terminal positif (+ ve) LED disambungkan ke GPIO2, seperti dalam skema di bawah, bukannya terminal negatif (-ve) LED yang disambungkan ke GPIO2, seperti dalam skema di atas. Mengikut jenis litar ini, kita perlu menarik GPIO2 ke keadaan HIGH, untuk menghidupkan LED, jika tidak, tarik GPIO2 ke keadaan LOW, untuk mematikan LED.

Oleh kerana, litar LED biru pada Hibiscus Sense adalah active-low, kami akan memprogramkannya seperti di bawah:

Penjelasan Sketsa Perincian

LED disambungkan ke GPIO2, kita perlu mengkonfigurasi GPIO2 sebagai OUTPUT.

Dalam void loop()fungsinya, program dimulakan dengan menghidupkan LED, kerana ciruit active-low, kami menggunakan keadaan LOW pada GPIO2 untuk menyelesaikan litar LED. Kemudian delay()berfungsi untuk menghentikan sebentar program dalam milisaat. Sebaliknya untuk mematikan LED.

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32, kemudian melihat hasilnya. Dengan melalui pemerhatian, output LED hanya mempunyai 2 keadaan, iaitu ON dan OFF, sehingga isyarat output ini dikenali sebagai DIGITAL OUTPUT.

Fakta menarik! Latihan ini meniru cahaya strobo di kapal terbang pada waktu malam.

## Latihan 2: Kawal LED Biru pada GPIO2 (Kesan Cahaya Bersinar)

Dalam latihan ini, kami akan menggunakan LED biru yang sama dalam Latihan 1 , tetapi menghasilkan kesan cahaya yang menyala, seperti gambar yang ditunjukkan di bawah. Di mana warna LED biru akan bermula dari MATI dan perlahan-lahan bercahaya sehingga mencapai kecerahan maksimum dan MATI lagi, berulang kali.

Seperti yang kita ketahui, isyarat output dari Latihan 1 adalah DIGITAL OUTPUT, di mana isyarat keluaran adalah ON atau OFF, tetapi untuk mencapai kesan cahaya menyala, kita memerlukan isyarat output yang mempunyai rentang nilai dari nilai minimum hingga maksimum.

Apa yang kita perlukan adalah Pulse-Width Modulation (PWM), di mana output isyarat yang telah dihasilkan oleh PWM, hampir ANALOG OUTPUT, tetapi bukan output analog gelombang sinus yang sebenarnya. PWM adalah teknik modulasi yang menghasilkan denyut lebar berubah dalam kitaran tugas isyarat digital (gelombang persegi), di mana rata-rata dari masa ke masa, ia mewakili isyarat output analog, seperti yang ditunjukkan dalam gambar di bawah.

Dengan isyarat output PWM, kita dapat mengawal kecerahan LED, kelajuan motor, kepanasan elemen pemanasan, getaran elemen piezo untuk kekuatan buzzer, arah motor servo dan isyarat audio termodulasi.

Berita baiknya ialah, ESP32 mempunyai 16 saluran PWM bebas yang boleh dikonfigurasi, yang dapat dikonfigurasikan untuk menghasilkan isyarat PWM pada semua GPIO, kecuali GPIO34 hingga GPIO39.

Sebelum pengaturcaraan langsung, mari kita bincangkan mengenai program untuk menghasilkan isyarat output PWM.

Biasanya di papan Arduino rasmi atau papan Arduino yang serasi, kami akan menggunakan fungsi analogWrite() untuk menghasilkan isyarat PWM. Oleh kerana saluran PWM ESP32 dapat dikonfigurasi, ia mempunyai 3 fungsi untuk mengkonfigurasi dan menghasilkan isyarat PWM, iaitu:

1. ledcSetup(_channel_, _frequency_, _resolution_) fungsi persediaan untuk pengawal PWM, dengan 3 argumen:
    - salurkan bilangan saluran PWM, dari 0 hingga 15.
    - frekuensi frekuensi isyarat PWM, untuk LED adalah 5 kHz.
    - menyelesaikan resolusi isyarat PWM, dari 1 bit hingga 16 bit, untuk LED kami akan menggunakan resolusi 8 bit.
2. ledcAttachPin(_gpio_, _channel_) berfungsi untuk menyatakan nombor GPIO LED dan saluran PWM, dengan 2 argumen:
    - gpio nombor GPIO untuk output isyarat PWM.
    - salurkan bilangan saluran PWM.
3. ledcWrite(_channel_, _dutycycle_) berfungsi untuk menghasilkan output isyarat PWM, dengan 2 argumen:
    - salurkan bilangan saluran PWM.
    - dutycycle nilai kitaran tugas PWM Untuk resolusi 8 bit, nilainya berkisar antara 0 - 255.

Sekali lagi, yang perlu diingat, litar LED biru pada Hibiscus Sense rendah-aktif, jadi kami akan memprogramkan LED untuk kesan bercahaya seperti berikut:

Penjelasan Sketsa Perincian

Dalam void setup()fungsi tersebut, ada dua fungsi untuk diprogram, pertama untuk mengkonfigurasi saluran PWM menggunakan ledcSetup()fungsi, dengan saluran 0PWM5 kHz , frekuensi 8 bitsPWM dan resolusi PWM .

Dalam void setup()fungsi tersebut, kami juga menyatakan GPIO mana yang akan menyampaikan output dari isyarat PWM menggunakan ledcAttachPin();fungsi, dengan nomor GPIO2 di mana LED biru dihubungkan dan saluran PWM0 .

Kedua-duanya berfungsi untuk mengkonfigurasi saluran PWM dan untuk menyatakan GPIO untuk isyarat output PWM telah dilakukan. Sekarang kita dapat menghasilkan isyarat PWM dengan menggunakan ledcWrite()fungsi di dalam void loopuntuk mengawal kecerahan LED biru untuk menghasilkan kesan LED biru bercahaya. Oleh kerana litar LED biru aktif rendah, nilai PWM (dari 255-0) perlu secara automatik penurunan 1 hingga 1 oleh, dari 255 hingga 254, dari 254 hingga 253, dari 253 hingga 252 dan seterusnya sehingga nilai mencapai nilai PWM minimum, 0. Oleh itu, for()fungsi digunakan untuk secara automatik menghasilkan pemboleh ubah penurunan nilai PWM dari 255-0 seperti berikut, di mana ledcWrite()fungsi tersebut berada di dalam for()fungsi:

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32, kemudian perhatikan hasilnya. Dengan observatoin, output LED biru adalah kesan cahaya bersinar berulang, yang dihasilkan dari penurunan nilai output isyarat PWM.

## Latihan 3: Kawal LED Biru pada GPIO2 (Kesan Cahaya Pernafasan)

Latihan ini adalah kesinambungan dari Latihan 2 .

Dalam Latihan 2, kami menggunakan fungsi for() untuk secara automatik menghasilkan penurunan nilai PWM dari 255-0 untuk (active-low circuit)menghasilkan output dari kesan cahaya bersinar, sementara dalam latihan ini kami menghasilkan efek cahaya pernafasan.

Sangat mudah ... kita hanya perlu menambahkan fungsi for() lain untuk menghasilkan kenaikan nilai PWM  dari 0-255 secara automatik, jadi program seperti berikut:

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32, kemudian perhatikan hasilnya. Seperti yang diperhatikan, output LED biru adalah kesan cahaya pernafasan berulang, yang dihasilkan dari penurunan dan kenaikan nilai signal PWM.

## Latihan 4: Kawal Buzzer Kecil pada GPIO13 (Melodi)

Buzzer adalah komponen elektronik piezoelektrik, yang menghasilkan nada ketika elemen piezo bergetar berdasarkan bekalan voltan yang diberikan, voltan yang berbeza akan menghasilkan getaran yang berbeza, sehingga menghasilkan nada yang berbeza. Oleh kerana ESP32 mempunyai kemampuan untuk menjana voltage using, pengawal bulit-in PWM, kami dapat menerapkannya pada buzzer kecil kami untuk menghasilkan nada.

Pada Hibiscus Sense, terdapat 1x buzzer kecil, dilabel sebagai BUZZER on-board, seperti yang dibulatkan pada gambar di bawah.

Voltan operasi buzzer kecil berkisar antara 2-4V dengan nilai voltan 3V, (+ve) terminalbuzzer disambungkan ke GPIO13, sementara (-ve) terminal sambungan disambungkan ke GND, seperti yang ditunjukkan dalam skema di bawah ini. Terminal ke-3 buzzer tidak disambungkan.

Untuk menghasilkan nada atau melodi dari buzzer, kita perlu menulis fungsi PWM untuk mengawal isyarat output PWM pada GPIO13. Dalam Latihan 2 dan Latihan 3 kami menggunakan ledcWrite(_channel_, _dutycycle_)fungsi untuk mengendalikan kecerahan LED, sementara untuk menghasilkan nada, ESP32 mempunyai fungsi lain yang dikenal sebagai ledcWriteTone(_channel_, _note_)fungsi, dengan 2 argumen:

    - salurkan bilangan saluran PWM.
    - perhatikan kekerapan catatan. Contoh, Catatan D4 = 147 Hz. Klik di sini untuk nada yang tersedia.

Dalam latihan ini, semua komen yang ada dan kekerapan untuk menghasilkan nada, telah diisytiharkan pada fail header, bertajuk tones.h seperti di sini untuk nada yang sedia ada.

Oleh kerana kita perhatikan, kita perlu menggunakan ledcWriteTone()fungsi bukan ledcWrite()fungsi untuk menghasilkan isyarat output PWM agar buzzer menghasilkan nada, mari tulis program seperti di bawah:

Penjelasan Sketsa Perincian

Pertama, kita perlu memasukkan fail tajuk, yang mempunyai pernyataan semua nota yang ada.

Dalam void setup()fungsi, kita harus mengkonfigurasi saluran PWM menggunakan ledcSetup()fungsi dan menyatakan terminal buzzer (+ ve) dilampirkan ke GPIO13 menggunakan ledcAttachPin()fungsi.

Di dalam void loop()fungsi, kami menggunakan ledcWriteTone()fungsi untuk menghasilkan suara NOTE_D4frekuensi, sementara ledcWrite()fungsi untuk mematikan bel. Oleh itu, pelaksanaan fungsi ini berulang kali, menghasilkan bunyi seperti penggera.

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32. Setelah selesai memuat naik, kita akan mendengar bunyi bip.

## Latihan 5: Komunikasi Bersiri (Hibiscus Sense & Computer)

Komunikasi Bersiri adalah proses komunikasi, menerima dan mengirimkan data antara dua peranti, seperti komputer ke komputer atau mikrokontroler ke komputer atau mikrokontroler ke mikrokontroler , dengan menerapkan protokol perkakasan yang dikenal sebagai UART (Universal Asynchronous Receiver/Transmitter). Data dihantar / diterima sedikit demi sedikit secara berurutan oleh UART melalui dua atau satu saluran penghantaran (wayar), dengan kelajuan yang boleh dikonfigurasi yang dikenali sebagai baud-rateatau bits-per-second(bps): 9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600 .

Dua saluran penghantaran UART, yang dikenali sebagai RX (receive)dan TX (transmit). Penghantaran bermula dengan menghantar data dari port TX satu pengawal UART ke port RX dari pengawal UART yang lain.

Pada Hibiscus Sense, UART0 telah dihubungkan ke Silicon Labs CP2104, yang memungkinkan kami membuat komunikasi bersiri antara komputer dan ESP32. UART0 juga digunakan untuk memuat naik program ke dalam ESP32. Sementara, UART1 telah digunakan untuk SPI flash untuk modul ESP32 dan UART1 RX telah digunakan untuk WS2812 RGB LED.

Walaupun, siri perkakasan sudah siap, ia tidak akan dimulakan, melainkan jika kita memprogramkan ESP32 untuk memulakan perkakasan bersirinya. Dalam pengaturcaraan Arduino, Library sedia ada untuk komunikasi bersiri, dikenali sebagai Serial. Kita boleh menggunakan Serial Library untuk memprogramkan ESP32 untuk komunikasi bersiri. Terdapat 5 fungsi utama di Serial Library untuk komunikasi bersiri, iaitu:

1. Serial.begin(_baud-rate_) fungsi, dengan 1 argumen:
    - baud-menilai kelajuan komunikasi bersiri.
2. Serial.print() fungsi menghantar data dan mencetak data pada Serial Monitor, dengan 1/2 argumen:
    - 1 hujah:
        - Serial.print(88) hantar dan cetak "88"
        - Serial.print(1.23456) hantar dan cetak "1.23" (lalai 2 tempat perpuluhan)
        - Serial.print('H') hantar dan cetak "H"
        - Serial.print("Hello, hibiscus!") hantar dan cetak "Helo, bunga raya!"
    - 2 hujah (pilihan) base number or decimal points:
        - Serial.print(88, BIN) hantar dan cetak "1011000"
        - Serial.print(88, OCT) hantar dan cetak "130"
        - Serial.print(88, DEC) hantar dan cetak "88"
        - Serial.print(88, HEX) hantar dan cetak "58"
        - Serial.print(1.23456, 0) hantar dan cetak "1"
        - Serial.print(1.23456, 2) hantar dan cetak "1.23"
        - Serial.print(1.23456, 4) hantar dan cetak "1.2345"
3. Serial.println()berfungsi sama seperti Serial.print(), dengan watak barisan baru.
4. Serial.available() penggunaan fungsi untuk memeriksa sama ada data tersedia dalam penyangga (menahan 64 bait).
5. Serial.read()fungsi digunakan untuk membaca data di dalam siri menerima buffer.

Kami telah memahami fungsi Serial Library utama , sekarang mari kita menulis program yang ESP32 dapat memancarkan nilai tambahan ke Arduino IDE's Serial Monitor. Program seperti di bawah:

Penjelasan Sketsa Perincian

Untuk membuat nilai tambahan, kita dapat menggunakan operator + (plus) kerana ini adalah operasi aritmetik tambahan . Kita boleh membuat pemboleh ubah global dengan initial value of 0 dan int jenis data integer.

Dalam void setup()fungsi tersebut, pertama kita perlu menginisialisasi komunikasi siri perkakasan dengan memanggil begin()fungsi Serial objek, dengan kecepatan baud yang sesuai, yang selalu digunakan adalah 9600.

Dalam pemikiran logik, sebelum kita dapat menyerahkan nilai apa pun, kita harus mempunyai nilai terlebih dahulu, sebelum kita dapat mengemukakannya, bukan? Oleh itu, dalam void loop()fungsi, perkara pertama yang harus dilakukan, adalah menjana nilai tambah pemboleh ubah counter, menerapkan (++) operasi aritmetik, mewakili +1 ke nilai pemboleh ubah pemboleh ubah sebelumnya. Contoh nilai sebelumnya counteradalah 0 kemudian tambahkannya dengan +1, nilai pembilang pembaharuan terbaru adalah 1, kerana proses perkara berada di dalam fungsi void loop(), nilai pembilang berubah secara bertahap sebanyak 1 setiap gelung.

Untuk menghantar nilai pembilang berubah dengan garis baru, kami menggunakan fungsi println()Serial objek, untuk melakukan tugas dengan merujuk pembilang pemboleh ubah pada argumen fungsi println().

berhenti sebentar sebelum meneruskan ke tindakan seterusnya.

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32, setelah selesai memuat naik, buka Serial Monitor. Hasil penilitian, kita dapat melihat nilai tambahan dengan garis baru dicetak pada Arduino IDE Serial Monitor.

## Latihan 6: Memantau Status Butang Tekan pada GPIP0 (LED ON / OFF)

Tombol tekan adalah suis seketika yang menutup litar semasa menekan butang, sementara butang dilepaskan, litar terputus, seperti yang ditunjukkan dalam animasi di bawah. Ia bukan suis togol, di mana ia mempunyai kedudukan ON dan OFF. Tombol tekan biasanya digunakan sebagai input untuk menggerakkan sistem.

Pada Hibiscus Sense, terdapat dua butang tekan:

    1. RST tekan butang untuk menetapkan semula program ESP32.
    2. IO0 disambungkan ke GPIO0.

Kedua-dua butang tekan dalam Hibiscus Sense menggunakan pull-up resistor, untuk mengelakkan voltan tergantung dengan kapasitor untuk memperbaiki kesan tekan tombol . Litar akan tamat apabila kita menekan butang IO0, maka ESP32 melihat keadaan LOW pada GPIO0, kerana GND dihubungkan ke persimpangan GPIO0 dalam litar, seperti yang ditunjukkan dalam skema di bawah.

Boleh jadi, sekiranya tombol tekan menggunakan pull-down resistor, seperti yang ditunjukkan dalam lakaran dibawah. ESP32 melihat keadaan HIGH pasa GPIO0 apabila tombol tekan IO0 ditekan, kerana 3.3V disambungkkan pada persimpangan GPIO0. ini bukanlah litar pada Hibiscus Sense.

Oleh kerana kita tahu bahawa ESP32 akan mengesan keadaan LOW pada GPIO0 ketika tombol tekan ditekan, maka programnya adalah seperti berikut:

Penjelasan Sketsa Perincian

Dalam fungsi void setup() kita menyatakan dua fungsi pinMode():

1. Untuk menyatakan GPIO0 sebagai pin INPUT, disambungkan ke Pushbutton.
2. Untuk menyatakan GPIO2 sebagai pin OUTPUT, disambungkan ke LED biru.

Dalam fungsi void loop() tersebut, kita ingin memantau keadaan GPIO0 berulang kali, sama ada LOW atau HIGH bergantung pada tindakan yang berlaku pada tombol tekan, sama ada ditekan atau dibebaskan.

1. Buat pemboleh ubah tempatan bernama pbstatus untuk menyimpan keadaan semasa GPIO.

2. Terapkan fungsi if() untuk membandingkan, sama ada nilai pbstatus pemboleh ubah sama dengan LOW atau yang lain ( HIGH). Sekiranya pbstatus == LOW, LED enyala dan jika pbstatus sama dengan selain LOW, LED akan terpadam.

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32. Sekarang kita akan melihat warna biru terpadam, kerana ia hanya akan menyala apabila kita menekan butang IO0.

## Latihan 7: Kawal LED RGB pada GPIO16

RGB LED adalah LED tiga warna dalam pakej:

- Merah
- Hijau
- Biru

LED RGB, mempunyai empat petunjuk, untuk setiap warna dan satu anod biasa (+ ve) atau katod biasa (-ve). Dalam common cathode LED RGB, tiga LED berkongsi satu (-ve) connection, manakala, dalam common anode LED RGB, tiga LED berkongsi satu (+ve) connection. Gambar di atas, menunjukkan bahawa LED RGB adalah katod biasa, kerana plumbum terpanjang adalah (-ve) plumbum. Kita boleh menggunakan pengawal PWM ESP32 untuk mengawal setiap plumbum LED RGB untuk menghasilkan warna yang berbeza.

Terdapat LED RGB 1x pada Hibiscus Sense yang dilabelkan sebagai WS2812LED RGB khas. WS2812 adalah LED RGB yang dapat dialamatkan yang dapat disambungkan secara bersiri. Kita dapat mengawal warna warna LED RGB pada posisinya, hanya dengan satu pin ke mikrokontroler ESP32, luar biasa!

WS2812 mempunyai 4 penyambung:

1. VDD- Bekalan kuasa 3.5 ~ 5.3V. 3.3V juga cukup untuk menghidupkan LED RGB.
2. DOUT - Mengawal output isyarat data.
3. VSS - Terminal GND.
4. DIN - Mengawal input isyarat data.

Skema WS2812 RGB pada Hibiscus Sense, seperti dalam gambar di bawah.

Untuk mengawal LED RGB biasa, kita dapat menghasilkan output isyarat PWM ke plumbum indivialnya untuk menghasilkan warna LED RGB yang berbeza. Oleh kerana, LED RGB kami pada Hibiscus Sense adalah WS2812, kami perlu menggunakan Adafruit_Neopixel Library untuk mengawal warna LED RGB menggunakan sambungan wayar tunggal. Sebelum memprogram ESP32, kita perlu memasang library dari  Arduino IDE Library Manager, seperti pada gambar di bawah.

Penjelasan Sketsa Perincian *

Termasuk Adafruit_Neopixelfail library header dan mengisytiharkan satu contoh nama rgb untuk Adafruit_NeoPixelkelas dan kedua-dua hujah, yang bilangan RGB LED: 1dan disambungkan kepada yang GPIO pin: 16.

Memulakan Adafruit_Neopixel library dengan fungsi begin().

Jika fungsi show() yang kita jalankan tanpa set warna, ia akan menghantar arahan OFF pada LED RGB. Kami memanggil fungsi ini setelah inisialisasi, kerana kami hanya ingin memastikan program warna sebelumnya kembali ke OFF semasa permulaan yang pertama.

Fungsi setPixelColor() adalah untuk mengatur kedudukan LED dan output warna LED RGB. Kombinasi warna RGB dari 0-255 seperti pada gambar di bawah, misalnya pada garis sketsa di bawah, MERAH: 255, HIJAU: 0 dan BIRU: 255, mewakili magenta.

Sekarang, kita boleh memuat naik lakaran lengkap ke ESP32, kemudian perhatikan hasilnya. Berdasarkan penilitian yang dibuat, output warna dari RGB LED adalah magenta.


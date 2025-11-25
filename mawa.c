#include <stdio.h>
#include <unistd.h>  // for sleep() and usleep()

void line(const char *text, int delay) {
    printf("%s\n", text);
    fflush(stdout);
    usleep(delay * 1000);
}

int main() {
    printf("\n🎤 Karaoke Mode: Maripoye Lokam 🎤\n");
    printf("👉 Start playing the song now!\n");
    printf("Lyrics will appear in sync...\n\n");
    sleep(3);

    line("Maripoye Lokam, Cheddollantha Ekam", 3200);
    line("Naajukaina Nabotodiki Dhinadinamoka Narakam", 3600);
    line("Yado Ledhu Lopam, Naameedhe Naakopam", 2800);
    line("Andhananna Aakashaniki Enthakani Egabadatham, Umm…", 4000);

    line("Oh, Evvarikevvaru Ayinollantu Unnagani Lere", 3400);
    line("Ey Vavi Varasa Peru Pilupu Anni Noti Chivare", 3400);
    line("Yaha Visugu Putti Inkipoye Kandallo Kanneere", 3400);
    line("Etu Theerigi Chudu Manaki Maname, One And Only Lover Ey", 3600);

    line("Dhimka Chikud Chithatha", 2000);
    line("Dhimka Chikud Chith Hoye Hoye", 2200);
    line("Dhimka Chikud Chithatha", 2000);
    line("Dhimka Chikud… Anna!", 2400);

    line("Sarra Sarra Suram", 1800);
    line("Surrantadhi Karam", 1800);
    line("Hey, Rappa Rappapa, Rabba Rabaribabba", 2200);
    line("Hey, Rappa Rappapa, Rabba Rabaribabba", 2400);

    printf("\n🎶 Song Ended — Hope You Enjoyed the Karaoke! 🎶\n");
    return 0;
}

#include <stdio.h>

//  *******************************************************
//  Nom ......... : ordi_papier
//  Auteur ...... : Mathilde Reveney
//  Version ..... : V0.1 du 04/08/2022
//  Licence ..... : Cours AdO de L1
//  Compilation : gcc -Wall ordi_papier.c
//  Usage : Pour exécuter : ./ordi_papier 10.5.txt (par exemple)
//  ********************************************************

typedef char *str;    // type string

//les variables
struct contexte {unsigned char RS; unsigned char RM; unsigned char PC; unsigned char OP; unsigned char AD; char A; unsigned char entree; enum UAL {add, sub, NAND} cet_UAL; unsigned char memoire[256];} ordi_papier;//la memoire etant representee par des variables unsigned char, on ne peut traiter que des nombres allant de 0 a 255. seul A peut avoir une valeur negative puisque nous avons besoin de tester si A < 0 dans l'OP code 11, cela dit elle n'est pas ecrite en memoire lorsque c'est le cas

//les microcodes
void mc_1(struct contexte *ce_contexte) { ce_contexte->RS = ce_contexte->PC; }
void mc_2(struct contexte *ce_contexte) { ce_contexte->PC = ce_contexte->RM; } //ne pas faire la phase 3
void mc_3(struct contexte *ce_contexte) { ce_contexte->A = ce_contexte->RM; }
void mc_4(struct contexte *ce_contexte) { ce_contexte->RM = ce_contexte->A;  }
void mc_5(struct contexte *ce_contexte) { ce_contexte->OP = ce_contexte->RM; }
void mc_6(struct contexte *ce_contexte) { ce_contexte->AD = ce_contexte->RM; }
void mc_7(struct contexte *ce_contexte) { ce_contexte->RS = ce_contexte->AD; }
void mc_8(struct contexte *ce_contexte) { ce_contexte->RM = ce_contexte->entree; }
void mc_9(struct contexte *ce_contexte) { printf("Sortie:%x \n", ce_contexte->RM); }
void mc_10(struct contexte *ce_contexte) { ce_contexte->cet_UAL = add; }
void mc_11(struct contexte *ce_contexte) { ce_contexte->cet_UAL = sub; }
void mc_12(struct contexte *ce_contexte) {
    if (ce_contexte->cet_UAL == add) { ce_contexte->A = ce_contexte->A + ce_contexte->RM; }
    else if (ce_contexte->cet_UAL == sub) { ce_contexte->A = ce_contexte->A - ce_contexte->RM; }
    else if (ce_contexte->cet_UAL == NAND) { ce_contexte->A = !(ce_contexte->A && ce_contexte->RM); } 
    }
void mc_13(struct contexte *ce_contexte) { ce_contexte->RM = ce_contexte->memoire[(int)ce_contexte->RS]; }
void mc_14(struct contexte *ce_contexte) { ce_contexte->memoire[(int)ce_contexte->RS] = ce_contexte->RM; }
void mc_15(struct contexte *ce_contexte) { ce_contexte->PC++; }
void mc_16(struct contexte *ce_contexte) { printf("Entrez une valeur: "); int buffer; scanf("%x", &buffer); ce_contexte->entree = (char)buffer; getchar(); } //GETCHAR() pour se debarasser de "\n" et avoir un tampon vide au prochain appel de la fonction printf("\n");
void mc_17(struct contexte *ce_contexte) { ce_contexte->cet_UAL = NAND; }

//les opcodes
void opcode_00(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_3(ce_contexte);}
void opcode_10(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_2(ce_contexte);}
    //passer ensuite a la phase 1
void opcode_11(struct contexte *ce_contexte){ if (ce_contexte->A < 0){mc_1(ce_contexte);mc_13(ce_contexte);mc_2(ce_contexte);}} //passer ensuite a la phase 1
void opcode_12(struct contexte *ce_contexte){ if (ce_contexte->A == 0){mc_1(ce_contexte);mc_13(ce_contexte);mc_2(ce_contexte);}} //passer ensuite a la phase 1

void opcode_20(struct contexte *ce_contexte){mc_10(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_21(struct contexte *ce_contexte){mc_11(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_22(struct contexte *ce_contexte){mc_17(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_40(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_3(ce_contexte);}
void opcode_41(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_9(ce_contexte);}
void opcode_48(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_4(ce_contexte);mc_14(ce_contexte);}
void opcode_49(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_16(ce_contexte);mc_8(ce_contexte);mc_14(ce_contexte);}
void opcode_60(struct contexte *ce_contexte){mc_10(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_61(struct contexte *ce_contexte){mc_11(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_62(struct contexte *ce_contexte){mc_17(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_C0(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_3(ce_contexte);}
void opcode_C1(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_9(ce_contexte);}
void opcode_C8(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_4(ce_contexte);mc_14(ce_contexte);}
void opcode_C9(struct contexte *ce_contexte){mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_16(ce_contexte);mc_8(ce_contexte);mc_14(ce_contexte);}
void opcode_E0(struct contexte *ce_contexte){mc_10(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_E1(struct contexte *ce_contexte){mc_11(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_E2(struct contexte *ce_contexte){mc_17(ce_contexte);mc_1(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_6(ce_contexte);mc_7(ce_contexte);mc_13(ce_contexte);mc_12(ce_contexte);}
void opcode_01(struct contexte *ce_contexte) {printf("Fin du programme \n");}//ajout d'une instruction qui permet de sortir de la boucle et mettre fin au programme

int main(int k, const str argv[]) {

    enum bool {false, true};
    enum bool opcode_inconnu = false;
    int lu, cycles = 0;
    FILE * zap = fopen(argv[1], "r") ;
    if (!zap) { printf("fichier pas lisible"); }
    int buffer;
    for (int i=0; i<256 && lu != EOF; i++) { lu = fscanf(zap, "%x", &buffer); ordi_papier.memoire[i] = (char)buffer; } //chaque valeur est chargee dans un tampon sous forme d'un int puis convertie en char avant d'etre enregistree dans la memoire
    for (int i=0; i<256; i++) { printf("%x ", ordi_papier.memoire[i]); 
        if ((i+1)%16==0) { printf("\n"); } }//pour afficher sous forme de matrice 16*16

    do {
        //phase 1
        mc_1(&ordi_papier);
        mc_13(&ordi_papier);
        mc_5(&ordi_papier);
        mc_15(&ordi_papier);

        //phase 2
        if (ordi_papier.OP == 00){opcode_00(&ordi_papier);}
        else if (ordi_papier.OP == 0x10){opcode_10(&ordi_papier);}
        else if (ordi_papier.OP == 0x11){opcode_11(&ordi_papier);}
        else if (ordi_papier.OP == 0x12){opcode_12(&ordi_papier);}
        else if (ordi_papier.OP == 0x20){opcode_20(&ordi_papier);}
        else if (ordi_papier.OP == 0x21){opcode_21(&ordi_papier);}
        else if (ordi_papier.OP == 0x22){opcode_22(&ordi_papier);}
        else if (ordi_papier.OP == 0x40){opcode_40(&ordi_papier);}
        else if (ordi_papier.OP == 0x41){opcode_41(&ordi_papier);}
        else if (ordi_papier.OP == 0x48){opcode_48(&ordi_papier);}
        else if (ordi_papier.OP == 0x49){opcode_49(&ordi_papier);}
        else if (ordi_papier.OP == 0x60){opcode_60(&ordi_papier);}
        else if (ordi_papier.OP == 0x61){opcode_61(&ordi_papier);}
        else if (ordi_papier.OP == 0x62){opcode_62(&ordi_papier);}
        else if (ordi_papier.OP == 0xC0){opcode_C0(&ordi_papier);}
        else if (ordi_papier.OP == 0xC1){opcode_C1(&ordi_papier);}
        else if (ordi_papier.OP == 0xC8){opcode_C8(&ordi_papier);}
        else if (ordi_papier.OP == 0xC9){opcode_C9(&ordi_papier);}
        else if (ordi_papier.OP == 0xE0){opcode_E0(&ordi_papier);}
        else if (ordi_papier.OP == 0xE1){opcode_E1(&ordi_papier);}
        else if (ordi_papier.OP == 0xE2){opcode_E2(&ordi_papier);}
        else if (ordi_papier.OP == 0x01){opcode_01(&ordi_papier); return 0;}
        else {printf("OP code inconnu \n"); opcode_inconnu = true;}

        cycles += 1;
        //phase 3
        if (ordi_papier.OP == 0x10) { } //pas de phase 3, on retourne au debut du cycle
        else if (ordi_papier.OP == 0x11 && ordi_papier.A < 0x0) { } //pas de phase 3, on retourne au debut du cycle
        else if (ordi_papier.OP == 0x12 && ordi_papier.A == 0x0) { } //pas de phase 3, on retourne au debut du cycle
        else { mc_15(&ordi_papier); }

    } while(!opcode_inconnu);//fin de la boucle en cas d'erreur d'OP code
    fclose(zap);

    return 0;
}
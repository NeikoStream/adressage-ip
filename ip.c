/******************************************************************************
*  ASR => M2101                                                               *
*******************************************************************************
*                                                                             *
*  N° de Sujet :  2                                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitulé : Analyse d’adresses IP                                           *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-prénom1 : Rousseau Nicolas                                             *
*                                                                             *
*  Nom-prénom2 : Philémon Hinfray--Cacheux                                    *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier :    ip.c                                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <inttypes.h> // bibliothèque pour utilisé les uint

//Procédure de détermination de la classe
void classe(int ip1)
{
    if (ip1 >= 1 && ip1 < 127)
    {
        printf("\nClasse A");
    }

    else if (ip1 > 127 && ip1 < 192)
    {
        printf("\nClasse B");
    }

    else if (ip1 >= 192 && ip1 < 224)
    {
        printf("\nClasse C");
    }

    else if (ip1 >= 224 && ip1 < 240)
    {
        printf("\nClasse D");
    }

    else if (ip1 >= 240 && ip1 <= 255)
    {
        printf("\nClasse E");
    }
}

//Procédure de détermination du type de l'ip
void type(int ip1, int ip2, int ip3, int ip4, int host2, int host3, int host4)
{

    if (host2 == 255 || host2 == 0 && host3 == 255 || host3 == 0 && host4 == 255 || host4 == 0)
    {
        printf("Cette adresse IP est une adresse broadcast.\n");
    }
    else
    {
        if (ip1 == 10)
        {
            printf("Type : privé\n");
        }
        else if (ip1 == 172 && ip2 >= 16 && ip2 <= 31)
        {
            printf("Type : privé\n");
        }
        else if (ip1 == 192 && ip2 == 168)
        {
            printf("Type : privé\n");
        }
        else if (ip1 == 127)
        {
            printf("Type : localhost\n");
        }
        else if (ip1 == 224 && ip2 == 0 && ip3 == 0)
        {
            printf("Type : multicast\n");
        }

        else
        {
            printf("Type : public\n");
        }
    }
}

void main()
{
    /************************ Déclaration des variables ***************************/
    uint8_t ip[4];     // tableau de 4 octet permetent de contenir chaque partie de l'ip
    uint8_t reseau[4]; // tableau rassemblant chaque partie de l'IP réseau
    uint32_t reseau2;  // Tableau ip réseau concaténé en 32 bits
    uint32_t host;     // Tableau ip host concaténé en 32 bits
    uint8_t host2[4];  // Tableau ip host concaténé en 32 bits
    uint32_t ip2;      // Tableau ip concaténé en 32 bits
    int masque;        // integer pour le masque
    /******************************************************************************/

    //Demande a l'utilisateur de saisir une adresse ip avec son masque
    printf("Entrer une adresse IP (format : 0.0.0.0/0):");

    //Scan d'entrer de l'utilisateur
    scanf("%hhu.%hhu.%hhu.%hhu/%d", &ip[0], &ip[1], &ip[2], &ip[3], &masque);

    // opérateurs de décalage permetant de placer les octet au bonne endroit et d'obtenir la concatenation des 4 octet de l'ip
    ip2 = (ip[0] << 24) + (ip[1] << 16) + (ip[2] << 8) + (ip[3]);

    printf("________________________________\n");




    /**************** Vérifications des valeurs rentrées avant la poursuite du programme ******************/
    if ((ip[0], ip[1], ip[2], ip[3]) >= 0 && (ip[0], ip[1], ip[2], ip[3] ) <= 255 && masque >= 0 && masque <= 32)
    {
    /******************************************************************************************************/




        //affichage de l'ipv4
        printf("\nipv4 : %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
        //Controle de la classe de l'ip saisie
        classe(ip[0]);

        /************************* Calculs et affichages des résultats *************************/

         //Calcul et affichage de l'adresse réseau
        reseau2 = ((ip2) >> (32 - masque)) << (32 - masque);
        reseau[0] = (reseau2 >> 24) & 0b11111111;
        reseau[1] = (reseau2 >> 16) & 0b11111111;
        reseau[2] = (reseau2 >> 8) & 0b11111111;
        reseau[3] = (reseau2)&0b11111111;

        printf("\nAdresse réseau : %u.%u.%u.%u", reseau[0], reseau[1], reseau[2], reseau[3]);

         //Calcul et affichage de l'adresse hôte
        host = ((ip2) << (masque)) >> (masque);
        host2[0] = (host >> 24) & 0b11111111;
        host2[1] = (host >> 16) & 0b11111111;
        host2[2] = (host >> 8) & 0b11111111;
        host2[3] = (host)&0b11111111;

        printf("\nAdresse host : %u.%u.%u.%u\n", host2[0], host2[1], host2[2], host2[3]);

         //Controle du type d'adressage ip
        type(ip[0], ip[1], ip[2], ip[3], host2[1], host2[2], host2[3]);

        /***************************************************************************************/
    }
    else
    {
        //si l'IP rentré n'est pas correct ->
        printf("L'IP ou le masque saisi n'est pas correct\n");
    }

    printf("________________________________\n");
    
}
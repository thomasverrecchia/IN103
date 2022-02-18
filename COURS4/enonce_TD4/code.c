#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hufftree.h"



/** \brief Fonction de parcours r�cursif de l'arbre de Huffman permettant
    de remplir la table des codes. Elle prend en argument un buffer dans
    lequel elle va stocker les diff�rents "bits" de codage rencontr�s au cours
    de la descente et recopiera, une fois arriv�e � un feuille, la cha�ne de
    ces "bits" dans l'entr�e de la table correspondant au caract�re de la
    feuille.
    \param tree : Noeud courant explor� de l'arbre.
    \param accu : Buffer pour stocker au fur et � mesure de la descente dans
    l'arbre les caract�res '0' et '1' des bits rencontr�s.
    \param accu_len : Nombre actuel de caract�res dans l'accu.
    \param codes : Table des codes � remplir.
    \return Bool�en disant si la m�morisation des code s'est pass�e
    correctement.
    \note Cette fonction est locale au fichier courant et n'est pas export�e.
    Elle sert uniquement de "helper" � la fonction \a get_codes. */
static bool tree_walk (struct huff_node_t *tree, char *accu, int accu_len,
                       char **codes)
{
  if (tree != NULL) {
    if (tree->left == NULL) {
      /* Noeud terminal. Notons que par invariant le fils droit doit �tre
         �galement � NULL. */
      codes[tree->letter] = malloc ((accu_len + 1) * sizeof (char)) ;
      if (codes[tree->letter] == NULL) return (false) ;
      strncpy (codes[tree->letter], accu, accu_len) ;
      codes[tree->letter][accu_len] = '\0' ;
      return (true) ;
    }
    else {
      /* Noeud non terminal, on r�curse � gauche et � droite en augmentant
         l'accumulateur. */
      accu[accu_len] = '0' ;
      if (! tree_walk (tree->left, accu, accu_len + 1, codes)) return (false) ;
      accu[accu_len] = '1' ;
      return (tree_walk (tree->right, accu, accu_len + 1, codes)) ;
    }
  }
  return (true) ;
}



/** \brief R�cup�ration de la table des codes associ�s � l'arbre de Huffman
    pass� en argument.
    \param tree : Pointeur sur la racine de l'arbre de Huffman.
    \return Tableau de 256 cha�nes de caract�res repr�sentant le code associ�
    � chaque caract�re (indexation par le code du caract�re). Chaque cha�ne
    est compos�e de caract�res '0' et '1' formant une repr�sentation textuelle
    du code binaire associ� au caract�re encod�. */
char** get_codes (struct huff_node_t *tree)
{
  int i ;
  /* Le cas le plus d�g�n�r� le code le plus long est �gal au nombre de
     symboles (ici 256) - 1. Il faut 1 octet de plus pour clore la cha�ne
     obtenue. Donc une longueur de cha�ne maximale de 256 caract�res. */
  char tmp_buffer[256] ;

  char **codes = malloc (257 * sizeof (char*)) ;
  if (codes == NULL) return (NULL) ;

  /* Initialisation des codes � "aucune cha�ne". */
  for (i = 0; i < 256; i++) codes[i] = NULL ;

  /* Parcours r�cursif de l'arbre pour remplir la table. */
  if (! tree_walk (tree, tmp_buffer, 0, codes))
    printf ("Error while building codes table. Table may be incomplete.\n") ;

  return (codes) ;
}

#include <stdio.h>
#include <stdbool.h>
#include "hufftree.h"



/** \brief D�codage du fichier compress� \a in_fname selon l'arbre de Huffman
    \a tree et �criture du r�sultat dans le fichier \a out_fname.
    \param in_fname : Fichier source � lire et d�coder.
    \param out_fname : Fichier destination dans lequel �crire le r�sultat du
    d�codage.
    \param tree : Arbre de Huffman ayant servi � compresser le fichier initial
    et dont le r�sultat de compression (� d�compresser) se trouve dans
    \a in_fname.
    \return Bool�en disant si la d�compression s'est pass�e sans erreur. */
bool decode (char *in_fname, char *out_fname, struct huff_node_t *tree)
{
  FILE *in, *out ;
  int c ;
  struct huff_node_t *current_node ;
  bool error = false ;

  in = fopen (in_fname, "rb") ;
  if (in == NULL) {
    printf ("Error. Unable to open input file '%s'.\n", in_fname) ;
    return (false) ;
  }

  out = fopen (out_fname, "wb") ;
  if (out == NULL) {
    printf ("Error. Unable to open output file '%s'.\n", out_fname) ;
    fclose (in) ;
    return (false) ;
  }

  /* Lecture "bit par bit", donc dans notre cas simplifi�, caract�re par
     caract�re du fichier d'entr�e et descente dans l'arbre de Huffman de
     la racine jusqu'� trouver une feuille. */
  c = fgetc (in) ;
  current_node = tree ;
  while ((! error) && (c != EOF)) {
    switch (c) {
    case '0':
      /* Descente � gauche. */
      current_node = current_node->left ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL left child.\n") ;
        error = true ;
      }
      /* Si le noeud est une feuille, il faut �crire le caract�re correspondant
         et repartir du haut de l'arbre. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '0'. */

    case '1':
      /* Descente � droite. */
      current_node = current_node->right ;
      if (current_node == NULL) {
        printf ("Error. Unexpected NULL right child.\n") ;
        error = true ;
      }
      /* M�me chose que pour la descente � gauche. */
      if ((current_node->left == NULL) && (current_node->right == NULL)) {
        fputc (current_node->letter, out) ;
        current_node = tree ;
      }
      break ;   /* Fin de case '1'. */

    default:
      /* Ne devrait jamais se produire puisque l'on n'a �crit que des
         caract�res '0' et '1'. */
      printf ("Error. Unexpected bit-like character in input stream.\n") ;
      error = true ;
      break ;
    }

    /* Lecture du prochain "bit" (caract�re). */
    c = fgetc (in) ;
  }   /* Fin de while (c != EOF). */

  /* Normalement, il ne devrait pas rester de "bits" en suspend, donc � la
     fin de la lecture du flot de biti on devrait se trouver de nouveau � la
     racine de l'arbre. Ca sentirait le bug ou le fichier corrompu. */
  if (current_node != tree) printf ("Warning. Spurious bit(s) remaining.\n") ;
  if (error) printf ("Error encountered.\n") ;

  fclose (in) ;
  fclose (out) ;
  return (true) ;
}

# ft_select

Le projet *ft_select* a pour but de nous faire manipuler les _termcaps_.

Le programme prend en entrée des arguments, l'utilisateur peut alors en sélectionner et les retourner au shell.


## Utilisation

Clonez le repository : https://github.com/Modaouche/ft_select.git 

Puis compilez avec le makefile `make` ou make `all` (make help pour plus d'information)

*ft_select* prend en entrée au moins un argument. L'utilisateur peut se déplacer dans les arguments avec les `touches fléchées` ou les `tabulations`. La sélection s'effectue avec `espace` et il est possible de supprimer des éléments avec `delete`. La touche `entrée` (`return`) permet de valider la sélection et de l'envoyer au shell. Enfin avec`r` vous avez la recherche d'element.

# ft_select
------

Le projet *ft_select* a pour but de nous faire manipuler les _termcaps_.

Le programme prend en entrée des arguments, l'utilisateur peut alors en sélectionner et les retourner au shell.


## Téléchargement

Clonage du dossier :

	$> git clone https://github.com/aguerin42/ft_select.git

La bibliothèque [Libft][] est nécessaire pour pouvoir compiler *ft_select*. Après avoir cloner le repo git, il faut mettre à jour et cloner le submodule de la _Libft_ :

	$> cd ft_select
	$> git submodule update --init libft
	$> cd libft && git checkout master && cd -


## Compilation

Le projet peut être compilé à l'aide de `make` ou `make all`. La compilation de la bibliothèque _Libft_ est automatiquement effectuée (son _Makefile_ est appelé depuis celui de *ft_select*). L'exécutable est nommé *ft_select*.

La commande `make clean` permet de supprimer tous les fichiers objets et `make fclean` de supprimer, en plus de ceux-ci, l'exécutable.

La commande `make re` est équivalent à `make fclean all`.

La documentation du code peut être générée à l'aide de [Doxygen][] grâce à la commande `make doxygen` et supprimée avec `make cleandoxy`. Elle est placée dans le dossier _Docs_.


## Utilisation

*ft_select* prend en entrée au moins un argument. L'utilisateur peut se déplacer dans les arguments avec les `touches fléchées` ou les `tabulations`. La sélection s'effectue avec `espace` et il est possible de supprimer des éléments avec `delete`. La touche `entrée` (`return`) permet de valider la sélection et de l'envoyer au shell.

Autres options
- `shift`+`A` : sélection de tous les arguments
- `shift`+`D` : désélection de tous les arguments
- `shift`+`S` : sélection de tous les arguments situés entre le curseur et le dernier argument sélectionné
- `shift`+`Z` : inversion de la sélection

[Libft]: https://github.com/Aguerin42/libft
[Doxygen]: https://github.com/doxygen/doxygen

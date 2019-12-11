# GalenaCpp - Documentation

![](E:\Pictures\Image1.png)

## Instructions

### afficher

`afficher <number/string>`

Permet d'afficher des éléments dans la console en avec retour à la ligne

### afficherl

`afficher <number/string>`

Permet d'afficher des éléments dans la console sans retour à la ligne

### appeler

`appeler <routine> [arg1, arg2, arg3, ...]`

Appele une routine en passant les arguments donner

### dessiner

`dessiner <routine> [xmin = -10, xmax = 10, xoff = 0.1, [arg1, arg2, arg3, ...]]`

Récupère pour chaque valeur x donnée à la routine, une valeur y correspond, puis affiche et relie les points sur un graph

### retourner

`retourner [valeur]`

Permet de terminer une [routine](#routines) en renvoyant une valeur facultative *valeur*

### saisir

`saisir <variable>`

Demande à l'utilisateur de saisir la valeur d'une variable

## Variables

Les noms de variables doivent commencer par une lettres, mais peuvent contenir des chiffres

`variable = valeur`

Une fois définie, la variable peut être utilisée dans un calcul, une condition, ou encore dans un appel de [routine](#routines)

## Calculs

Opérateurs disponibles: `+, -, *, /, ^, ++, --, ()`

## Boucles conditionnelles

### Conditions

Opérateurs conditionnels: `non, et, ou, ==, >, >=, <, <=`

### Si, alors, sinon

```
si <condition>
alors
	<instructions>
sinon
	<instructions>
fin
```

Exécute le premier jeu d'instructions si la condition est respectée, sinon le seconde

### Tant que, faire

```
tant que <condition>
faire
	<instructions>
fin
```

Exécute le jeu d'instructions tant que la condition est respectée

### Répéter

```
répéter <variable> = <min>:<max>
faire
	<instructions>
fin
```

Répète le jeu d'instructions pour <variable> allant de <min> à <max>. <variable> est une variable en lecture, sa modification n'affecte pas la boucle

## Routines

```
<routine>: [arg1, arg2, arg3, ...]
	
	<instructions>
	
	retourner [valeur]
```

Crée une routine appelée <routine> prenant en argument *arg1*, *arg2*, *arg3* (si définis), exécute le jeu d'instructions et renvoie *valeur* si donnée
# Guide de contribution

## Pré-requis

Pour pouvoir commencer à développer sur ce projet, vous devez disposer de l'éditeur de code Qt Creator.

Le développement sera effectué avec la version 6.7 de Qt, pouvant évoluer. la version à utiliser sera systématiquement stipulée ici.

## Langue du projet

Nous avons fait le choix de communiquer exclusivement en __français__ partout dans les outils liés à Reaulight.  
Les fichiers markdown, commentaires, entrées de CHANGELOG, outils CLI, messages de commit et tickets   
doivent donc être rédigés en français uniquement.

Le code, lui, à l'exception des commentaires, doit être exclusivement en anglais, pas de variable ou de nom de migration en français.

Attention ⚠️, cela ne veut pas dire que Reaulight n'est pas traduit : Il sera traduit lorsque le projet aura un peu plus avancé. 

## Branches Git

Pour nommer ses branches, le projet utilise le modèle appelé « Git Flow ».
Voir [cette page](https://git-flow.readthedocs.io/fr/latest/presentation.html) pour plus de détails sur ce workflow,
mais voici un tuto rapide :

Les deux branches principales qui **existent en permanence** sont :
- `master` : la branche sur laquelle se trouve l'application telle qu'elle a été releasée en dernier.
  On ne peut y merger que des branches `release/x.x.x` ou `hotfix/x.x.x`. Aucun commit ne doit y être ajouté directement.
  Cette branche est considérée comme la "branche stable releasée".
- `develop` : la branche sur laquelle on merge toutes les branches de nouvelles fonctionnalités (nommées `feature/...`).
  On peut aussi y faire quelques commits directs, uniquement quand il s'agit de petites corrections.
  Cette branche est considérée comme la "branche stable non-releasée".

Quand vous voulez modifier le code, commencez par créer une branche `feature/nom-de-la-fonctionnalité`, qui est basée sur `develop`.
Ensuite, utilisez cette branche pour créer une pull-request dont la branche de destination est `develop`.
Avant d'être mergée, le fonctionnement de l'application sur cette branche doit impérativement être stable et dépourvu de bug.
Une fois la PR mergée, la branche doit être supprimée.

## Version et Changelog

Reaulight utilise [Semantic Versionning (semver)](https://semver.org/lang/fr/) pour ses numéros de version. La version courante est 
définie dans le fichier `/VERSION` dans la branche `master`.

Un fichier de changelog existe à la racine du projet, il doit être mis à jour au fil des évolutions du projet. 

## Diffusion de version

`Non encore implémenté pour le moment.`

## Tests

`Non encore implémenté pour le moment.`

## Structure du logiciel

`Non encore implémenté pour le moment.`

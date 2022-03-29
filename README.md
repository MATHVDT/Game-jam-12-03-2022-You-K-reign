# Game-Jam-12-03-2022
 
**Date :** 12-13 mars 2022   
**Thème :** À la carte   
**Nom du jeu :** You(k)reign

## Pitch du jeu 

Bienvenue dans notre Jeu **Your (k) Reign**. Voici les règles du jeu :

Vous incarnez le leader d’une île qui produit un certain type de ressource. Votre île produit 3 fois par tour la ressource de votre île. Votre envie est d’aller conquérir les îles autour de vous afin d’être le leader de toutes ces îles. Pour faire cela, vous avez plusieurs possibilités comme faire la guerre avec une autre île. Pour cela, des points d’actions et des ressources vous sont demandés. Pour réaliser une tentative de guerre par exemple, il vous suffit de cliquer sur le bouton *Guerre militaire* et ensuite de cliquer sur l’île que vous souhaitez attaquer. Chaque ressource que vous possédez et qui est demandé pour attaquer permettra une augmentation d’un certain pourcentage vos chances de succès d’attaque. Lorsque vous attaquerez une île, ses alliés vous déclareront alors la guerre, cela vous empêchera d’acheter leur ressource ou alors le prix sera plus élevé. Si vous réussissez l’attaque, l’île sera annexée à la vôtre. Après cela, vous récupérerez deux fois la ressource qu’elle produit par tour. Il y a d’autres types d’attaque, comme la guerre par la religion. Celle-ci réussit en fonction du pourcentage de présence de votre religion dans l’île. Pour avoir un max de pourcentage, vous devez donc convertir les autres îles. Vous pouvez également faire des accords commerciaux avec les autres îles afin d’acheter leur ressource moins chère. Mais cet accord ne dure que quelques tours alors attention ! Pour faire certains types d’action, vous avez besoin de certaines ressources plus évoluées, pour les obtenir vous devez transformer vos ressources. Lorsque vous décidez de transformer vos ressources, vous transformez tout ce qu’il est possible de transformer. Amusez-vous bien !

## Détails du jeu  

Vous possédez l'ile au centre de l'écran et votre but est de conquérir toutes les autres iles. Pour cela, vous disposez de 5 points d'actions par tour. A chaque tour, vous pouvez effectuer plusieurs actions possibles :

- Passer un **accord commercial** avec une ile
- **Acheter une ressource** à une ile
- **Convertir** la population d'une ile
- **Guerre religieuse** une ile
- **Guerre militaire** une ile
- **Transformer** les ressources  

Lorsque vous lancez une guerre contre une ile, vous avez une certaine probabilité de la capturer.  
 Dans le cas où l'attaque réussit et que vous capturez l'ile, les autres iles en alliance avec elle se dévoilent et se mettent en guerre contre vous pendant au moins 5 tours.  
 Vous ne pouvez donc plus passer un **Accord commercial** ou **Acheter une ressource** avec elle.   
Au début de chaque tour, vous produisez 3 ressources de votre ile ainsi que 2 ressources des iles capturées. Les iles non capturées produisent elles 3 ressources qui seront achetables si vous n'êtes pas en guerre avec elle.


### Détails des actions possibles 

- Passer un **accord commercial** avec une ile
> Permet d'acheter des ressources à l'iles pour seulement 1 point d'action.  
> Cet accord commercial dure 3 tours et peut être annulé si vous capturez une ile allié à celui-ci.  
> Vous ne pouvez pas passer d'accord commercial avec une ile qui est en guerre contre vous. 

> Coût : 2 points d'action 

- **Acheter une ressource** à une ile
> Le nombre de ressources que vous vous pouvez acheter par tour est limité à la production de l'ile. *(3 ressources/tour)*  
> Vous ne pouvez pas achetez de ressources à une ile qui est en guerre contre vous.  

> Coût : 2 points d'action (ile sans accord commercial) 

> Coût : 1 points d'action (ile avec accord commercial) 


- **Convertir** la population d'une ile
> Permet de convertir une partie de la population afin de faciliter l'attaque religieuse par la suite.

> Taux de conversion : *(Taux cumulable)* 
> - 5% de base
> - 10% de base avec une ressource primaire
> - 25% de base avec une ressource secondaire   

> Coût : 1 points d'action 


- **Guerre religieuse** une ile
> Lance une attaque religieuse sur l'ile. La probabilité de capturer l'ile est égale au taux de conversion de l'ile *(% en bas droite de l'ile)*.

> Coût : 2 points d'action   


- **Guerre militaire** une ile
> Lance une attaque militaire sur l'ile. La probabilité de capturer l'ile est dépend du nombre de ressources **diférentes** possédées.

> Taux de réussite de l'attaque : *(Taux cumulable)* 
> - 15% de base par ressource primaire
> - 35% de base par ressource secondaire 

> Coût : 2 points d'action 


- **Transformer** les ressources 
> Transforme toutes les ressources primaires possibles en ressources secondaires.

> Coût : 3 points d'action 

---
## Membre de la Team :
DERMIGNY Flavien  
PREVOT Pierre    
VILLEDIEU DE TORCY Mathieu    

---
## Code

**Compilation :**  `cd ./src && make && ./yourKreign.exe` 

**Executable du jeu :** *youKreign.exe*

---  

## Repas du week-end
### Repas du samedi midi :
Repas au [RU](https://usine.crous-clermont..fr/restaurant/resto-u-restocezo/) avec les autres équipes

### Repas du samedi soir
Pizza commandée par l'équipe Pixel au [Milano Pizza](https://milano-pizza-63-71.webself.net/)
  
Pierre  : 4 fromages (Large, base crème)  
Mathieu : Calzone La forestière   
Flavien : *Repas non communiqué* (en déplacement)


### Repas du dimanche midi : 
 
Pierre  : Salade de Lentille  
Mathieu : Wrap crudité jambon + Petits bâtons du berger (Auchan) + Pompote du [BDE ISIMA](https://bde.isima.fr/)  
Flavien : Lentilles vinaigre + Saucisse de Montbéliard


---
## Évènements divers

Flavien en déplacement le samedi dans la journée.

Fin du diapo de présentation du [projet de ZZ2](https://gitlab.isima.fr/fldumas5/genealogie) pour Mathieu.

Panne de voiture le dimanche matin, après avoir laissé les phares allumés toute la nuit. (PS : c'est une [Twingo](https://www.renault.fr/vehicules-particuliers/twingo.html))

---
## Objectifs

- [x] Faire un diagramme de classe qui claque 
- [x] Faire un jeu fonctionnel 
- [x] S'amuser 
- [x] Être fier de son jeu 
- [ ] Mettre des petits bâtiments sur les iles :'( 


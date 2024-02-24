# Programming Assignment 2
## Concept of Parallel and Distributed Processing


## Problem 1: Minotaur's Birthday Party
The Minotaur invited N guests to his birthday party. When the guests arrived, he made
the following announcement.
The guests may enter his labyrinth, one at a time and only when he invites them to do
so. At the end of the labyrinth, the Minotaur placed a birthday cupcake on a plate. When
a guest finds a way out of the labyrinth, he or she may decide to eat the birthday
cupcake or leave it. If the cupcake is eaten by the previous guest, the next guest will find
the cupcake plate empty and may request another cupcake by asking the Minotaur’s
servants. When the servants bring a new cupcake the guest may decide to eat it or leave
it on the plate.
The Minotaur’s only request for each guest is to not talk to the other guests about her or
his visit to the labyrinth after the game has started. The guests are allowed to come up
with a strategy prior to the beginning of the game. There are many birthday cupcakes, so
the Minotaur may pick the same guests multiple times and ask them to enter the
labyrinth. Before the party is over, the Minotaur wants to know if all of his guests have
had the chance to enter his labyrinth. To do so, the guests must announce that they have
all visited the labyrinth at least once.
Now the guests must come up with a strategy to let the Minotaur know that every guest
entered the Minotaur’s labyrinth. It is known that there is already a birthday cupcake left
at the labyrinth’s exit at the start of the game. How would the guests do this and not
disappoint his generous and a bit temperamental host?



## Problem 2

The Minotaur decided to show his favorite crystal vase to his guests in a dedicated
showroom with a single door. He did not want many guests to gather around the vase
and accidentally break it. For this reason, he would allow only one guest at a time into
the showroom. He asked his guests to choose from one of three possible strategies for
viewing the Minotaur’s favorite crystal vase:
1) Any guest could stop by and check whether the showroom’s door is open at any time
and try to enter the room. While this would allow the guests to roam around the castle
and enjoy the party, this strategy may also cause large crowds of eager guests to gather
around the door. A particular guest wanting to see the vase would also have no
guarantee that she or he will be able to do so and when.
2) The Minotaur’s second strategy allowed the guests to place a sign on the door
indicating when the showroom is available. The sign would read “AVAILABLE” or
“BUSY.” Every guest is responsible to set the sign to “BUSY” when entering the
showroom and back to “AVAILABLE” upon exit. That way guests would not bother trying
to go to the showroom if it is not available.
3) The third strategy would allow the quests to line in a queue. Every guest exiting the
room was responsible to notify the guest standing in front of the queue that the
showroom is available. Guests were allowed to queue multiple times.

I decided to go along with the third strategy. The advantage is that it's really easy
to organize and understand for all the guests and the system. No guest can go twice 
before all of the guests go if they're all lined up. The disadvantage is that the 
guests have to wait in a line as opposed to roaming freely like in the first option,
but in my eyes it's the most fair.

The code allows for the user to choose any amount of guests at the start and there's
a 1 second wait time for the guests to look at the vase between turns. It's coded
below in problem2.cpp

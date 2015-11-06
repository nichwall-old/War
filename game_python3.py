# Quick game to play war

import random

# Player decks
player1 = []
player2 = []

def shuffleDeck():
	suits = ['D_','C_','S_','H_']
	nums = ['1','2','3','4','5','6','7','8','9','10','A','K','Q','J']

	# Create cards
	deck = []
	for i in range(len(suits)):
		for j in range(len(nums)):
			deck.append(suits[i]+nums[j])

	# Shuffle deck
	for i in range(4000):
		first = random.randint(0,len(deck)-1)
		second = random.randint(0,len(deck)-1)

		temp = deck[first]
		deck[first] = deck[second]
		deck[second] = temp

	# Return deck
	return deck

def dealCards(deck):
	for i in range(len(deck)):
		if i%2==0:
			player1.append(deck[i])
		else:
			player2.append(deck[i])

def playerHasWon():
	if (len(player1)==0):
		print("Player 2 won!")
	elif (len(player2)==0):
		print("Player 1 won!")
	return ( len(player1)==0 or len(player2)==0 )

def compareTopCards(index=0):
	# Get cards
	p1 = player1[index][-1]
	p2 = player2[index][-1]

	# Check if they're the same
	if p1 == p2:
		return 0

	# Convert player 1
	try:
		p1 = eval(p1)
	except:
		if p1=="A":
			p1 = 14
		elif p1=="K":
			p1 = 13
		elif p1=="Q":
			p1 = 12
		elif p1=="J":
			p1 = 11
	# Convert player 2
	try:
		p2 = eval(p2)
	except:
		if p2=="A":
			p2 = 14
		elif p2=="K":
			p2 = 13
		elif p2=="Q":
			p2 = 12
		elif p2=="J":
			p2 = 11

	if ( p2==2 and p1==14 ):
		return 2
	elif (p1==2 and p2==14):
		return 1
	elif ( p1 > p2 ):
		return 1
	else:
		return 2

def breakTie():
	winner = 0
	cardCount = 0
	while winner == 0:
		cardCount += 4
		winner = compareTopCards(cardCount)
	return cardCount, winner

def displayGraph():
	outStr = ""
	for i in range(len(player1)):
		outStr += "#"
	for i in range(len(player2)):
		outStr += "."
	return outStr

def main():
	print("Dealing cards...")
	dealCards( shuffleDeck() )
	print("Cards Dealt!")
	outStr = "P1 Size\tP1 Played\tP2 Played\tP2 Size\tGraph\n"
	loopCount = 0
	while ( not playerHasWon() ):
		loopCount += 1
		if loopCount%100000 == 0:
			print(loopCount,len(player1),len(player2))
		state = compareTopCards()
		# Check if player 1 won
		if state == 1:
			player1.append(player2.pop(0))
		# Check if player 2 won
		elif state == 2:
			player2.append(player1.pop(0))
		# Break ties
		else:
			cardsWon, winner = breakTie()
			for i in range(cardsWon):
				if winner == 1:
					player1.append(player2.pop(0))
				else:
					player2.append(player1.pop(0))

		# Print out the current state, and append to output string
		graph = displayGraph()
		#print graph
		outStr += str(len(player1))+"\t\t\t"+str(len(player2))+"\t"+graph+"\n"

	file = open("gameData.txt",'w')
	file.write(outStr)
	file.close()

main()

var prompt = require('sync-prompt').prompt;

var card;

function generateCards(){
    var cardDeck = [];	
    var cardID = 0;
    for(var i = 0; i < 4; i++){
	var suite = "";
	for(var j = 2; j < 15; j++){
		//var card = '0';
	    switch(i){
		case 0:
		suite = '♠';
		break;
		case 1:
		suite = '♥';
		break;
		case 2:
		suite = '♦';
		break;
		case 3:
		suite = '♣';
		break;
	}//end switch
	    if (j < 11){
		card = j;
		}
	    else{
		if(j===11){
		    card = "Jack";
		    }
		if(j===12){
		    card = "Queen";
		    }
		if(j===13){
		    card = "King";
		    }
		if(j===14){
		    card = "Ace";
		    }
		}//end else

	var card = {Suite:suite, Card:card};
	cardDeck.push(card);
	cardID++;
}//end inner for
}//end outer for

    return cardDeck;
}//end generate function

function shuffle(cardDeck){
	
	
    var newDeck = [];
    var removedCount = 0;
	
    while(removedCount < 53){
		var shuffleIndex = Math.floor(Math.random() * cardDeck.length);		
		//ORIGNALvar cardToAdd = cardDeck.slice(shuffleIndex, shuffleIndex+1);
		var cardToAdd = cardDeck[shuffleIndex];
		//var cardToAdd = cardDeck.splice(shuffleIndex,1);
	    newDeck.push(cardToAdd);
	    removedCount++;
	
		}//end while loop

    return newDeck;
};//end shuffle function

function calculateHand(hand){
	
    var handTotal = 0;
    var aceCount = 0;


    for(var i = 0; i < hand.length; i++){
	
		if(hand[i].Card !== "Jack" && hand[i].Card !== "King" && hand[i].Card !== "Ace" && hand[i].Card !== "Queen"){
	    handTotal = hand[i].Card + handTotal;
	    }//end if
	
		else if (hand[i] !== "Ace") {
		handTotal = handTotal+ 10;
		}
		
		else{
	    handTotal = handTotal+ 11;
	    aceCount++;
	    }
	}//end for

    if (handTotal > 21){
	 	for(var j = 0; j < aceCount; j++){
	     	handTotal = handtotal - 10;
	     	}
	 }//end if
    return handTotal;
};//end calculatehand


function determineWinner(Number1, Number2){
    var winner; 

    if(Number1 > 21 && Number2 > 21){
	winner = "tie";
		}
		
    else if(Number1 > 21 && Number2 <22){
	winner = "Computer";
		}
		
    else if(Number1 < 22 && Number2 > 21){
	winner = "Player";
		}
		
    else{
		var playerDiff = 21 - Number1;
		var computerDiff = 21 - Number2;
		
			if(playerDiff < computerDiff){
	    	winner = "Player";
	    		}
			
			else if(playerDiff === computerDiff){
			winner = "tie"	
			}
			else{
	    	winner = "Computer";
	    		}
	}//end else

    return winner
};//end determine winner


function driver(){

	var dealtDeck = generateCards();
	var shuffledDeck = shuffle(dealtDeck);
    var playerHand = [];
	var compHand = [];
	

	while(shuffledDeck.length >= 26){
		var bust = "";
		
		var index = Math.floor(Math.random() * shuffledDeck.length);
		var toPush = shuffledDeck[index];
		playerHand.push(toPush);
		shuffledDeck.splice(index,1);
		
		index = Math.floor(Math.random() * shuffledDeck.length);
		toPush = shuffledDeck[index];
		compHand.push(toPush);
        shuffledDeck.splice(index,1);
		

		index = Math.floor(Math.random() * shuffledDeck.length);
		toPush = shuffledDeck[index];
		playerHand.push(toPush);
		shuffledDeck.splice(index,1);

		index = Math.floor(Math.random() * shuffledDeck.length);
		toPush = shuffledDeck[index];
		compHand.push(toPush);
		shuffledDeck.splice(index,1);

  		console.log("PLayer hand is", playerHand[0], ".....", playerHand[1], "for a total of", calculateHand(playerHand));		
		var hitOrstay = prompt("Would you like to (h)it or (s)tay?");
		while(hitOrstay === "h"){
			var hitRandom = Math.floor(Math.random() * shuffledDeck.length);
			toPush = shuffledDeck[hitRandom];
			playerHand.push(toPush);
			shuffledDeck.splice(hitRandom,1);
			
			if(calculateHand(playerHand) > 21){
				bust = "bust";
				break;
			}
			console.log("New card is", toPush, "for a total of", calculateHand(playerHand));
			hitOrstay = prompt("Would you like to (h)it or (s)tay?");
			}		
		
		console.log("");
		console.log("comp hand is", compHand[0], ".....", compHand[1], "for a total of", calculateHand(compHand));
		console.log("");
		
		if(bust !== "bust"){
		while(calculateHand(compHand) < 18){
			var compHit = Math.floor(Math.random() * shuffledDeck.length);
			toPush = shuffledDeck[compHit];
			compHand.push(toPush);
			shuffledDeck.splice(compHit,1);
			console.log("Computer new card is ", toPush, "for a total of ", calculateHand(compHand));
		}
		

		var king = determineWinner(calculateHand(playerHand), calculateHand(compHand));
		if(king === "tie"){
			console.log("The game is a tie!");
		}
		else{
		console.log("The winner is", king, "!!");
		}
		}
		
		else{
			console.log("player busts, computer wins!");
		}
		
	playerHand.splice(0, playerHand.length);
	compHand.splice(0,compHand.length);
	console.log("There are ", shuffledDeck.length, " cards left in the deck");
	console.log("--------------------------");
	console.log("");
	}
};
//}
//end driver

driver();

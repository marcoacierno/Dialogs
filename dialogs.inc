/**
	* Dialogs
	* Autore: ReVo_
	* Github: https://github.com/rrev
	
	* Version: 1.00
	* Changelog:
	*   1.00:
	*       Prima versione
	
*/
#define MAX_FUNC_NAME       25
//#define DEBUG

new DIALOGS_PlayerDialog[MAX_PLAYERS][MAX_FUNC_NAME];

stock ShowPlayerDialogEx(playerid, function[MAX_FUNC_NAME], style, caption[], info[], button1[], button2[])
{
	//if (strlen(function) > MAX_FUNC_NAME) return 0; pawn da un errore se si supera questo limite

	DIALOGS_PlayerDialog [playerid] = function;
	ShowPlayerDialog(playerid, 0, style, caption, info, button1, button2);
	return 1;
}

#define ShowPlayerDialog    ShowPlayerDialogEx

#define Dialog:%1(%2,%3,%4,%5) \
	forward DIALOGS_%1(%2,%3,%4,%5); \
	public DIALOGS_%1(%2,%3,%4,%5)

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	//la gamemode non ha ancor afatto vedere nessun td oppure è capito il bug del riavvio del server
	//in questo caso non fa nnt
	if (DIALOGS_PlayerDialog[playerid][0] == '\0') {
	    return 0;//ritorno 0 manda il dialog a qualche altro script
	}

	//CallLocalFunction crasha quando viene passata una stringa vuota
	// controllo se è vuota '\0' ultimo carattere è metto uno spazio vuoto
	if (inputtext[0] == '\0') { // is null
	    inputtext[0] = ' ';
	}
	
	#if defined DEBUG
	printf("OnDialogResponse(%d, %d, %d, %d, %s)", playerid, dialogid, response, listitem, inputtext);
	#endif
	
	new sz[31];
	format(sz, sizeof sz, "DIALOGS_%s", DIALOGS_PlayerDialog[playerid]);

	#if defined DEBUG
	printf("Player Function: %s - Will be called: %s", DIALOGS_PlayerDialog[playerid], sz);
	#endif
	
	DIALOGS_PlayerDialog[playerid] = "";
	CallLocalFunction(sz, "iisi", playerid, listitem, inputtext, response);
	return 1;//abbiamo un dialogo corrispondente quindi lo invio
}

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif

#define OnDialogResponse dialogs_OnDialogResponse
forward dialogs_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);


/**
	* Dialogs
	* Autore: ReVo_
	* Github: https://github.com/rrev
	
	* Version: 1.02 beta-1
	* Changelog:
	*	1.02-beta1:
	*		Aggiunto Dialog_Reopen(playerid) per riaprire l'ultimo dialog
	*   1.01:
	*	 	Piccola modifica
	*   1.00:
	*       Prima versione
	
*/
#define _dialogs_DEBUG

//new DIALOGS_PlayerDialog[MAX_PLAYERS][_dialogs_MAX_FUNC_NAME];
#define MAX_DIALOG_FUNCTION_SIZE	25
#define MAX_DIALOG_INFO_SIZE		128
#define MAX_DIALOG_CAPTION_SIZE		128
#define MAX_DIALOG_BUTTON_SIZE		20	 // 20

enum _e_dialogs_pDialog
{
	dialogs_Function[MAX_DIALOG_FUNCTION_SIZE],
	dialogs_style,
	dialogs_caption [MAX_DIALOG_CAPTION_SIZE],
	dialogs_info [MAX_DIALOG_INFO_SIZE],
	dialogs_button1 [MAX_DIALOG_BUTTON_SIZE],
	dialogs_button2 [MAX_DIALOG_BUTTON_SIZE],
}

new _dialogs_pDialog[MAX_PLAYERS][_e_dialogs_pDialog];

stock ShowPlayerDialogEx(playerid, function[MAX_DIALOG_FUNCTION_SIZE], style, caption[MAX_DIALOG_CAPTION_SIZE], info[MAX_DIALOG_INFO_SIZE], button1[MAX_DIALOG_BUTTON_SIZE], button2[MAX_DIALOG_BUTTON_SIZE])
{
	//if (strlen(function) > MAX_FUNC_NAME) return 0; pawn da un errore se si supera questo limite

	_dialogs_pDialog [playerid][dialogs_Function] = function;
	_dialogs_pDialog [playerid][dialogs_style] = style;
	_dialogs_pDialog [playerid][dialogs_caption] = caption;
	_dialogs_pDialog [playerid][dialogs_info] = info;
	_dialogs_pDialog [playerid][dialogs_button1] = button1;
	_dialogs_pDialog [playerid][dialogs_button2] = button2;
	
	//DIALOGS_PlayerDialog [playerid] = function;
	ShowPlayerDialog(playerid, 0, style, caption, info, button1, button2);
	return 1;
}

stock Dialog_Reopen(playerid)
{
	ShowPlayerDialog(playerid, _dialogs_pDialog [playerid][dialogs_Function], _dialogs_pDialog [playerid][dialogs_style], _dialogs_pDialog [playerid][dialogs_caption], _dialogs_pDialog [playerid][dialogs_info], _dialogs_pDialog [playerid][dialogs_button1], _dialogs_pDialog [playerid][dialogs_button2]);
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
	if (_dialogs_pDialog [playerid][dialogs_Function][0] == '\0') {
	    return 0;//ritorno 0 manda il dialog a qualche altro script
	}

	//CallLocalFunction crasha quando viene passata una stringa vuota
	// controllo se è vuota '\0' ultimo carattere è metto uno spazio vuoto
	if (inputtext[0] == '\0') { // is null
	    inputtext[0] = ' ';
	}
	
	#if defined _dialogs_DEBUG
	printf("OnDialogResponse(%d, %d, %d, %d, %s)", playerid, dialogid, response, listitem, inputtext);
	#endif
	
	new sz[31];
	format(sz, sizeof sz, "DIALOGS_%s", _dialogs_pDialog [playerid][dialogs_Function]);

	#if defined _dialogs_DEBUG
	printf("Player Function: %s - Will be called: %s", _dialogs_pDialog [playerid][dialogs_Function], sz);
	#endif
	
	//can create bugs
	//_dialogs_pDialog[playerid][dialogs_Function][0] = '\0';
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

#include <a_samp>
#include <dialogs>
#include <zcmd>

forward OneSecTimer();

main()
{
	print("\n----------------------------------");
	print("  This is a blank GameModeScript");
	print("----------------------------------\n");

	//printf("GetVehicleComponentType %u",GetVehicleComponentType(1100));

}

public OnGameModeInit()
{
	// Set timer of 1 second.
	SetTimer("OneSecTimer", 1000, 1);
	print("GameModeInit()");
	SetGameModeText("Timer Test");
	AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
	//test();
	return 1;
}

public OneSecTimer() {
//	new sText[256];
//	format(sText,sizeof(sText),"GetTickCount = %d",GetTickCount());
//	print(sText);
//	SendClientMessageToAll(0xFF0000, sText);
}

public OnPlayerConnect(playerid)
{
   // ShowPlayerDialog(playerid, "lalunghezzamaxedi20", DIALOG_STYLE_LIST, "Regole", "Non usare cheats\nNon imbrogliare\nNon nominare il nome di dio invano\nblabla", "Accetto", "Rifiuto");
	return 1;
}

public OnPlayerSpawn(playerid)
{
   // ShowPlayerDialog(playerid, "alloracomeva", DIALOG_STYLE_MSGBOX, "Tutto bene?", "Come stai?", "Bene", "Male");
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    return 0;
}

COMMAND:dialog_reopen(playerid, params[]) {
	ShowPlayerDialog (playerid, "TestDialog", DIALOG_STYLE_MSGBOX, "Riaprire", "Vuoi riaprire questo dialog?", "Si", "No");
	return true;
}

Dialog:TestDialog(playerid, listitem, inputtext[], response)
{
	if (response) {
	    print ("Si");
		Dialog_Reopen(playerid);
	}
	else {
	    print ("No");
	    Dialog_ReopenDiff (playerid, .style = DIALOG_STYLE_INPUT, .function = "CloseYes");
	}
	return true;
}

Dialog:CloseYes(playerid, listitem, inputtext[], response)
{
	SendClientMessage (playerid, -1, "Good bye!");
	return 1;
}

Dialog:lalunghezzamaxedi20(playerid, listitem, inputtext[], response)
{
	new sz[40];
	format(sz, sizeof sz, "Hai cliccato sulla regola #%d !", listitem);
	SendClientMessage(playerid, -1, sz);

	if (response)
	{
	    SendClientMessage(playerid, -1, "fa piacere!");
		Dialog_Reopen(playerid);
	}
	else
	{
	    SendClientMessage(playerid, -1, "Non ti piacciono queste regole?");
	    ShowPlayerDialog(playerid, "comepossomigliorarle", DIALOG_STYLE_INPUT, "come posso", "Come posso migliorarle?", "Ok", "No");
	}
	return 1;
}

Dialog:comepossomigliorarle(playerid, listitem, inputtext[], response)
{
	new sz[40];
	format(sz, sizeof sz, "Il tuo consiglio: %s - Grazie", inputtext);
	SendClientMessage(playerid, -1, sz);
	return 1;
}

Dialog:alloracomeva(playerid, listitem, inputtext[], response)
{
	if (response) {
	    SendClientMessage (playerid, -1, "Fa piacere!");
	}
	else {
	    SendClientMessage (playerid, -1, "Dispiace!");
	}
	return 1;
}


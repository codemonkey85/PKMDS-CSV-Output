#include "main.h"
int main(int argc, char* argv[])
{
	if (argv[1] != NULL)
	{
		try
		{
			opendb("veekun-pokedex.sqlite");
			bw2sav_obj * sav = new bw2sav_obj();
			pokemon_obj * pkm = new pokemon_obj();
			read(argv[1], sav);
			ofstream myfile;
			myfile.open("output.txt");
			ostringstream o;
			std::wstring wstr;
			o << "Name,Nickname,HPIV,AtkIV,DefIV,SpAtkIV,SpDefIV,SpdIV,HPEV,AtkEV,DefEV,SpAtkEV,SpDefEV,SpdEV,BoxName,BoxNumber,Slot,OTName,TID,SID\n";
			for (int pslot = 0; pslot < sav->cur.party.size; pslot++)
			{
				pkm = &(sav->cur.party.pokemon[pslot]);
				decryptpkm(pkm);
				if (pkm->species != Species::NOTHING)
				{
					o << lookuppkmname(pkm) << ",";
					wstr = getpkmnickname(pkm);
					o << std::string(wstr.begin(), wstr.end()) << ",";
					o << int(pkm->ivs.hp) << ",";
					o << int(pkm->ivs.attack) << ",";
					o << int(pkm->ivs.defense) << ",";
					o << int(pkm->ivs.spatk) << ",";
					o << int(pkm->ivs.spdef) << ",";
					o << int(pkm->ivs.speed) << ",";
					o << int(pkm->evs.hp) << ",";
					o << int(pkm->evs.attack) << ",";
					o << int(pkm->evs.defense) << ",";
					o << int(pkm->evs.spatk) << ",";
					o << int(pkm->evs.spdef) << ",";
					o << int(pkm->evs.speed) << ",";
					o << "N/A" << ",";
					o << int(0) << ",";
					o << int(pslot + 1) << ",";
					wstr = getpkmotname(pkm);
					o << std::string(wstr.begin(), wstr.end()) << ",";
					o << pkm->tid << ",";
					o << pkm->sid;
					o << "\n";
				}
			}
			for (int box = 0; box < 24; box++)
			{
				for (int bslot = 0; bslot < 30; bslot++)
				{
					pkm = &(sav->cur.boxes[box].pokemon[bslot]);
					decryptpkm(pkm);
					if (pkm->species != Species::NOTHING)
					{
						o << lookuppkmname(pkm) << ",";
						wstr = getpkmnickname(pkm);
						o << std::string(wstr.begin(), wstr.end()) << ",";
						o << int(pkm->ivs.hp) << ",";
						o << int(pkm->ivs.attack) << ",";
						o << int(pkm->ivs.defense) << ",";
						o << int(pkm->ivs.spatk) << ",";
						o << int(pkm->ivs.spdef) << ",";
						o << int(pkm->ivs.speed) << ",";
						o << int(pkm->evs.hp) << ",";
						o << int(pkm->evs.attack) << ",";
						o << int(pkm->evs.defense) << ",";
						o << int(pkm->evs.spatk) << ",";
						o << int(pkm->evs.spdef) << ",";
						o << int(pkm->evs.speed) << ",";
						wstr = getboxname(&(sav->cur), box);
						o << std::string(wstr.begin(), wstr.end()) << ",";
						o << int(box + 1) << ",";
						o << int(bslot + 1) << ",";
						wstr = getpkmotname(pkm);
						o << std::string(wstr.begin(), wstr.end()) << ",";
						o << pkm->tid << ",";
						o << pkm->sid;
						o << "\n";
					}
				}
			}
			string str = o.str();
			myfile << str;
			myfile.close();
			closedb();
		}
		catch (char* strg)
		{
			cout << "Exception raised: " << strg << endl;
		}
	}
	else
	{
		cout << "No argument supplied for save file!\n";
	}
	return 0;
}

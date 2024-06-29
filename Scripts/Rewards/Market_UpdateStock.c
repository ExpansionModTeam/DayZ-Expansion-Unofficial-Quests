class CustomMission: MissionServer
{
    override void Expansion_OnQuestCompletion(ExpansionQuest quest)
    {
        super.Expansion_OnQuestCompletion(quest);

        switch (quest.GetQuestConfig().GetID())
        {
            case 40: // Quest ID 40
                ExpansionMarketTraderZone traderZone = GetTraderZoneByName("ZoneFileName");
                if ( traderZone )
                {
                    //! Add items like this to given zone
                    traderZone.AddStock("anticheminjector", 10);
                    traderZone.AddStock("bandagedressing", 50);
                    traderZone.AddStock("epinephrine", 20);
                    traderZone.AddStock("morphine", 20);
                    traderZone.AddStock("salinebag", 20);
                    traderZone.AddStock("charcoaltablets", 20);
                    traderZone.AddStock("disinfectantalcohol", 20);
                    traderZone.AddStock("painkillertablets", 20);
                    traderZone.AddStock("tetracyclineantibiotics", 20);
                    traderZone.AddStock("vitaminbottle", 20);

                    //! Save the stock changes
                    traderZone.Save();
                }
            break;
        }
    }

    ExpansionMarketTraderZone GetTraderZoneByName(string zoneName)
    {
        auto traderObjects = ExpansionTraderObjectBase.GetAll();
        ExpansionTraderObjectBase traderObj;
        ExpansionMarketTraderZone traderZone;
        ExpansionMarketTrader trader;

        for (int i = 0; i < traderObjects.Count(); i++)
        {
            traderObj = traderObjects[i];
            if (!traderObj)
                continue;

            traderZone = traderObj.GetTraderZone();
            if (!traderZone)
                continue;
            
            if (traderZone.m_FileName == zoneName)
                return traderZone;
        }

        return NULL;
    }
};
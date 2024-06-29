class CustomMission: MissionServer
{
    override void Expansion_OnQuestContinue(ExpansionQuest quest)
    {
        super.Expansion_OnQuestContinue(quest);

        switch (quest.GetQuestConfig().GetID())
        {
            // In this example we want to fail the quest 10 or quest 22 if the player logged of or crashed
            // before completing the quest
            case 10:
            case 40: // Quest ID 40
            {
                ExpansionQuestModule questModule;
                if (!CF_Modules<ExpansionQuestModule>.Get(questModule))
                    return;

                questModule.CancelQuestServer(quest);
            }
            break;
        }
    }
};
class CustomMission: MissionServer
{
	override bool Expansion_CanCompleteQuest(ExpansionQuest quest, PlayerIdentity identity)
	{
		if ( !super.Expansion_CanCompleteQuest(quest, identity) )
			return false;

		switch (quest.GetQuestConfig().GetID())
		{
			case 45: // Quest ID
                // ItemName, Minimun Quantity required, liquid ID, How many Items required
				if ( !QuestLiquidCheck(identity, "rag_honey_jar", 0.75, 131072, 3) )
				{
					NotificationSystem.Create( new StringLocaliser( "Quest Honey" ), new StringLocaliser( "Not Enough" ), ExpansionIcons.GetPath("Bottle"), ARGB(255, 249, 201, 1), 4.0, identity );
					return false;
				}
			break;
			case 46: // Quest ID
                // ItemName, Minimun Quantity required, liquid ID, How many Items required
				if ( !QuestLiquidCheck(identity, "waterbottle", 0.8, 4096, 6) )
				{
					NotificationSystem.Create( new StringLocaliser( "Quest Beer" ), new StringLocaliser( "Not Enough" ), ExpansionIcons.GetPath("Bottle"), ARGB(255, 249, 201, 1), 4.0, identity );
					return false;
				}
			break;
		}

		return true;
	}

	bool QuestLiquidCheck(PlayerIdentity identity, string name, float PercentageMin, int liquidType, int requiredAmount)
	{
		// We grab the player
		PlayerBase player = PlayerBase.ExpansionGetPlayerByIdentity(identity);
		if ( !player )
			return false;
		
		// We retrieve all the rag_honey_jar from the player inventory
		array<ItemBase> items = GetItemsFromEntity(player, name);
		if ( !items || items.Count() < 1 )
			return false;
		
		// And we check each rag_honey_jar until we find one which match all our conditions
		int amountOfValidItems = HasEnoughLiquids(items, PercentageMin, liquidType);

		return amountOfValidItems >= requiredAmount;
	}

	int HasEnoughLiquids(array<ItemBase> items, int percentMin, int liquid)
	{
		int count;
		foreach(ItemBase item: items)
		{                
			// Quantity need to be at LEAST 80% full
			if ( item.GetQuantity() < item.GetQuantityMax() * percentMin )
				continue;

			if ( item.GetLiquidType() == liquid ) // eg. LIQUID_HONEY
				count++;
		}

		return count;
	}

	array<ItemBase> GetItemsFromEntity(EntityAI entity, string classname)
	{
		if(!entity)
			return NULL;
		
		if(classname == string.Empty)
			return NULL;
			
		array<EntityAI> itemsArray = new array<EntityAI>;
		array<ItemBase> itmArr = new array<ItemBase>;

		entity.GetInventory().EnumerateInventory(InventoryTraversalType.INORDER, itemsArray);
		for(int i = 0; i < itemsArray.Count(); i++)
		{
			if(itemsArray[i] != NULL)
			{
				if(itemsArray[i].IsKindOf(classname))
				{
					itmArr.Insert(ItemBase.Cast(itemsArray[i]));
				}
			}
		}
		
		return itmArr;
	}
};

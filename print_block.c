void	print_block(t_block *block)
{
	int			i;
	t_command	*cmd;
	t_redirect	*curr;

	while (block)
	{
		cmd = block->command;
		if (cmd && (cmd->argv || cmd->redirect))
		{
			curr = cmd->redirect;
			while (curr)
			{
				printf("======REDIRECTION======\n");
				printf("type: %d\n", curr->io_type);
				printf("file_name: %s\n", curr->file_name);
				printf("delimiter: %s\n", curr->delimiter);
				printf("========================\n");
				curr = curr->next;
			}
			i = 0;
			while (block->command->argv[i])
			{
				if (i == 0)
					printf("cmd: %s\n", block->command->argv[i]);
				else
					printf("argv: %s\n", block->command->argv[i]);
				i++;
			}
		}
		printf("****************************\n");
		block = block->next;
	}
}
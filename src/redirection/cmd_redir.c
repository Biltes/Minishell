/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biltes <biltes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:24:50 by migupere          #+#    #+#             */
/*   Updated: 2024/07/02 19:23:36 by biltes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
static int	expand_file_mane(t_shell *shell, char **file)
{
    int	len;

    if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
    {
        print_error(shell, *file, "ambiguous redirect", 1);
        return (0);
    }
    expand_arg(shell, file);
    len = ft_strlen(*file);
    trim_arg(*file);
    trim_quotes(*file, &len);
    free(*file); // Free file string
    return (1);
}*/
/*
void	run_redir(t_shell *shell, t_redir_node *cmd)
{
    int		fd;
    int		original_fd;

    original_fd = dup(cmd->fd);
    fd = -2;
    if (expand_file_mane(shell, &cmd->file))
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
    if (fd == -1)
        print_error(shell, cmd->file, strerror(errno), 1);
    else if (shell->status == CONTINUE)
    {
        dup2(fd, cmd->fd);
        close(fd);
        run_cmd(shell, cmd->cmd);
    }
    check_error_and_exit(dup2(original_fd, cmd->fd), "dup2 error", 1);
}
*/
static int expand_file_mane(t_shell *shell, char **file)
{
    int len;

    if (ft_strchr(*file, '$') && ft_strchr(*file, '*'))
    {
        print_error(shell, *file, "ambiguous redirect", 1);
        return 0;
    }

    expand_arg(shell, file);
    len = ft_strlen(*file);
    trim_arg(*file);
    trim_quotes(*file, &len);

    // Não liberar `*file` aqui, porque pode ser usado posteriormente
    return 1;
}
/*
void run_redir(t_shell *shell, t_redir_node *cmd)
{
    int fd;
    int original_fd;

    original_fd = dup(cmd->fd); // Duplica o descritor de arquivo original
    if (original_fd == -1)
    {
        perror("dup error");
        return;
    }

    fd = -2; // Inicializa fd com um valor inválido para detectar erros
    if (expand_file_mane(shell, &cmd->file))
    {
        // Abrir o arquivo com os modos especificados
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
    }

    if (fd == -1) // Verifica se a abertura do arquivo falhou
    {
        print_error(shell, cmd->file, strerror(errno), 1);
    }
    else if (shell->status == CONTINUE) // Continua se o status do shell permitir
    {
        if (dup2(fd, cmd->fd) == -1) // Duplica o fd para o descritor especificado
        {
            perror("dup2 error");
            close(fd);
            return;
        }
        close(fd); // Fecha o fd original
        run_cmd(shell, cmd->cmd); // Executa o comando com a redireção
    }

    // Restaura o descritor de arquivo original
    if (dup2(original_fd, cmd->fd) == -1)
    {
        perror("dup2 restore error");
    }
    close(original_fd); // Fecha o descritor duplicado
}
*/
/* 2
void run_redir(t_shell *shell, t_redir_node *cmd)
{
    int fd;
    int original_fd;

    printf("Redirecionamento de entrada/saída para: %s\n", cmd->file);

    original_fd = dup(cmd->fd); // Duplica o descritor de arquivo original
    if (original_fd == -1)
    {
        ft_putstr_fd("Erro ao duplicar o descritor de arquivo\n", STDERR_FILENO);
        return;
    }

    fd = -2; // Inicializa fd com um valor inválido para detectar erros
    if (expand_file_mane(shell, &cmd->file))
    {
        // Abre o arquivo com o modo apropriado baseado no comando
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
        if (fd == -1)
        {
            ft_putstr_fd("Erro ao abrir o arquivo para redirecionamento\n", STDERR_FILENO);
            return;
        }
    }

    if (fd != -1 && shell->status == CONTINUE)
    {
        if (dup2(fd, cmd->fd) == -1) // Duplica o fd para o descritor especificado
        {
            ft_putstr_fd("Erro ao duplicar o descritor de arquivo para redirecionamento\n", STDERR_FILENO);
            close(fd);
            return;
        }
        close(fd);
        run_cmd(shell, cmd->cmd); // Executa o comando com a redireção
    }

    if (dup2(original_fd, cmd->fd) == -1) // Restaura o descritor de arquivo original
    {
        ft_putstr_fd("Erro ao restaurar o descritor de arquivo original\n", STDERR_FILENO);
    }
    close(original_fd);

    printf("Redirecionamento concluído para: %s\n", cmd->file);
}
*/


/* teste1
void run_redir(t_shell *shell, t_redir_node *cmd)
{
    int fd;
    int original_fd;

    printf("Tentando redirecionar para: %s com modo: %d\n", cmd->file, cmd->mode);

    // Duplicar o descritor de arquivo original para armazenar o estado atual
    original_fd = dup(cmd->fd);
    if (original_fd == -1)
    {
        ft_putstr_fd("Erro ao duplicar o descritor de arquivo original\n", STDERR_FILENO);
        return;
    }

    fd = -2;
    if (expand_file_mane(shell, &cmd->file))
    {
        // Abrir o arquivo com os modos especificados (O_APPEND para >>)
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS);
        printf("Arquivo %s aberto com descritor %d e o modo é %d, o fd guardado é %d\n", cmd->file, fd, cmd->mode, cmd->fd);
        if (fd == -1)
        {
            ft_putstr_fd("Erro ao abrir o arquivo para redirecionamento\n", STDERR_FILENO);
            return;
        }
    }
	printf("oi\n");
    if (fd != -1 && shell->status == CONTINUE)
    {
        if (dup2(fd, cmd->fd) == -1) // Duplica o fd para o descritor especificado (cmd->fd)
        {
            ft_putstr_fd("Erro ao duplicar o descritor de arquivo para redirecionamento\n", STDERR_FILENO);
            close(fd);
            return;
        }
		printf("2i\n");
        close(fd);
		printf("4i\n");
        printf("Redirecionamento de descritor %d para %d concluído\n", fd, cmd->fd);
        run_cmd(shell, cmd->cmd); // Executa o comando com a redireção
    }
	printf("o43i\n");
    if (dup2(original_fd, cmd->fd) == -1) // Restaura o descritor de arquivo original
    {
        ft_putstr_fd("Erro ao restaurar o descritor de arquivo original\n", STDERR_FILENO);
    }
	printf("o4343i\n");
    close(original_fd);
}*/
void run_redir(t_shell *shell, t_redir_node *cmd)
{
    int fd;
    int original_fd;

    original_fd = dup(cmd->fd);
    if (original_fd == -1)
        return;
    fd = -2;
    if (expand_file_mane(shell, &cmd->file))
    {
        fd = open(cmd->file, cmd->mode, FILE_PERMISSIONS); // Certifique-se de usar O_RDONLY para leitura
        if (fd == -1)
		{
			print_error(shell, cmd->file, strerror(errno), 1);
            return;
		}
    }
    if (fd != -1 && shell->status == CONTINUE)
    {
        if (dup2(fd, cmd->fd) == -1)
		{
            close(fd);
            return;
		}
        close(fd);
        run_cmd(shell, cmd->cmd);
    }

    if (dup2(original_fd, cmd->fd) == -1)
    {
        return ;
    }
    close(original_fd);
}


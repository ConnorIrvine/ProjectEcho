# ADDING CODE

1. ``Git checkout main``: This will bring you into your local main
2. ``Git fetch``,``Git pull``: This will pull all changes that you do not have in your local main branch before starting another
3. ``Git checkout -b your_branch_name`` : Creating your branch
4. Make your changes
5. Stage your changes using VSCode built in source control
    a. Open Source Control
    b. Select the plus for each file you want to commit
6. ``Git commit -m "your_message_here"``
7. ``Git push`` OR if it is your first time pushing ``Git push origin/your_branch_name`` : Pushing your changes to be visible in the repository

Friendly note please prefix all commit messages with **fix:** or **feat:** depending on if what you are doing constitutes a new feature or a fixture of existing code or logic. Another friendly reminder that you need to save your files before staging/commiting using *Ctrl + S* in VSCODE.
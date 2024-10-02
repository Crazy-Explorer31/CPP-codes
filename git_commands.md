# *Base GIT commands*

# Local work

## 1. git commit
Adds new change from where you are.
### Options:
* `-m "[your message]" # adds message to commit`
* `--amend` # adds index to last commit, changes its message
### Usage:
```
git commit
git commit -m "Style"
git commit --amend
```

## 2. git checkout
Changes current branch or commit.
### Options:
`-b [branch_name] # creates new branch`
### Usage:
```
git checkout [already_created_branch]
git checkout -b [new_branch]
```
## 3. git branch
Creates new branch on current position. 

Or changes branch's position (with `-f`)
### Usage:
```
git branch [new_branch]

git branch -f [moved_branch] # moves to HEAD
git branch -f [moved_branch] [position_to_move]
```

## 4. git merge
Creates commit from merging of current and specified branches.
### Usage:
```
git merge [branch to merge]
```
## 5. git rebase
Moves sequence of changes of one branch to another one. Can be interactive.

Attention! Hashed of rebased commits will be changed, old commits will be deleted. In any mode
### Usage:
```
git rebase [branch, where you moving current branch changes to]
git rebase -i [branch, where you moving current branch changes to]
	# in auto-opened menu choose needed commits and their order
```
### Illustration:
# **TODO**
## 6. HEAD
When you use `checkout` command, you change your position in a repository. This position is called as HEAD. By default, HEAD is your last commit.

If your last `checkout` was to some branch, your commits would automaticly be directed to current branch. Else, your have a detached HEAD, and all branches are out of it.
## 7. relative links
In some git commands like `checkout` you may have to write a specific branch or commit. Commit can be pointed by its hash, but it's boring to search it. So, you can specify position of needed commit, using only his distance from HEAD. 

For example, commit behind current one is HEAD^. Two steps back -- HEAD~2.

Switch to the second parent of HEAD -- HEAD^2.

You also can compose ^ and ~.
### Usage:
```
git checkout HEAD^
git checkout HEAD~2
git checkout HEAD^2~5
```
## 8. git reset
If you need to roll back to some commit on current branch, deleting last commits, -- `reset` is for you! Moreover, you can turn working directory and index in a condition as you want.
### Options:
```
git reset --soft [commit] # rolled changes moved to index
git reset --mixed [commit] # rolled changes moved to work-dir. 
			     index is clear. BY DEFAULT
git reset --hard [commit] # workdir and index match current commit
```
### Usage:
```
git reset --soft HEAD~2
```
## 9. git revert
Creates new commit, absolutely opposite of specified.
### Usage:
```
git revert HEAD # suppress the last commit
git revert HEAD~2 # suppress some commit
```
## 10. git cherry-pick
Copies commits to HEAD. Doesn't delete commits
### Usage:
```
git cherry-pick [commit_1] [commit_2] ... # paste commits to HEAD
```
## 11. git tag
Creates name for specified commit.
### Usage:
```
git tag [tag_name] [commit]
```
## 12. git describe
Prints info about the neariest tagged commit.
### Usage:
```
git descibe # prints: [tag_name]_[how far]_g[hash of tagged]
```

---
# Remote work

## 13. git clone
Creates local copy of remote repository
### Usage:
```
git clone [url]
```
## 14. Remote branches
When you have had a copy of repo, there are local and remotes branches. Work with local was described in a previous paragraph. But remote only points to condition of remote repo (when it was last updated). 

Remote branches are called as `origin/main`, `origin/side` and etc. They cannot be moved.
## 15. git fetch
Loads to remote branches commits from repo. Remoted branches are updated. Useful, when your local commits have conflicts with remoted.
### Usage:
```
git fetch # loads to all remoted branches
git fetch origin [from]:[to]
git fetch origin [from]: # creates new [from] branch
# loads commits from remoted branch [from] to local branch [to]
```
## 16. git pull
Also used for loading remoted commits, but smarted than `git fetch`. After fetching it merges local branches with respective remoted. If you want your local commits to be rebased to remoted, use `--rebase` flag.

### Usage:
```
git pull # loads to all remoted branches
git pull --rebase
```
## 17. git push
Send your work to repo. Remoted branches are updated.

From-To semantics is similar to `git fetch`.
### Usage:
```
git push
git push origin [from]:[to]
git push origin :[to] # deletes [to] branch
```
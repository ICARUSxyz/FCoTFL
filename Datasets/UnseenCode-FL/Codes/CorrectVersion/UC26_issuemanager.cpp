#include "issuemanager.h"

IssueManager::IssueManager(QObject *parent, QString _proFileName) : QObject(parent), proFileName(_proFileName)
{
    undefinedIssueList = QList<std::shared_ptr<ClassUndefinedSyntaxIssue>>();

    unspecifiedIssueList = QList<std::shared_ptr<ClassMemberUnspecifiedIssue>>();
}

void IssueManager::appendUndefinedIssue(const QList<ClassUndefinedSyntaxIssue> &list)
{
    for(int i = 0; i < list.size(); i++){
        ClassUndefinedSyntaxIssue issue = list.at(i);
        std::shared_ptr<ClassUndefinedSyntaxIssue> sp = std::make_shared<ClassUndefinedSyntaxIssue>(issue);
        undefinedIssueList.append(sp);
    }
}

void IssueManager::appendUnspecifiedIssue(const QList<ClassMemberUnspecifiedIssue> &list)
{
    for(int i = 0; i < list.size(); i++){
        ClassMemberUnspecifiedIssue issue = list.at(i);
        std::shared_ptr<ClassMemberUnspecifiedIssue> sp = std::make_shared<ClassMemberUnspecifiedIssue>(issue);
        unspecifiedIssueList.append(sp);
    }
}

QList<std::shared_ptr<ClassUndefinedSyntaxIssue> > IssueManager::getUndefinedIssueList() const
{
    return undefinedIssueList;
}

QList<std::shared_ptr<ClassMemberUnspecifiedIssue> > IssueManager::getUnspecifiedIssueList() const
{
    return unspecifiedIssueList;
}

void IssueManager::clearUndefinedIssueList()
{
    undefinedIssueList.clear();
}

void IssueManager::clearUnspecifiedIssueList()
{
    unspecifiedIssueList.clear();
}


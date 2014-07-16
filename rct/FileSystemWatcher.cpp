#include "FileSystemWatcher.h"

void FileSystemWatcher::processChanges(const Changes &changes)
{
    struct {
        Signal<std::function<void(const Path&)> > &signal;
        const Set<Path> &paths;
    } signals[] = {
        { mAdded, changes.files[Changes::Add] },
        { mRemoved, changes.files[Changes::Remove] },
        { mModified, changes.files[Changes::Modified] }
    };

    const unsigned count = sizeof(signals) / sizeof(signals[0]);
    for (unsigned i=0; i<count; ++i) {
        for (Set<Path>::const_iterator it = signals[i].paths.begin(); it != signals[i].paths.end(); ++it) {
            signals[i].signal(*it);
        }
    }
}
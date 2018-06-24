#include <algorithm>
#include "TrainProfilesModel.h"

namespace breathe_trainer{

    TrainProfile TrainProfilesModel::getProfileByName(const std::string &str) {
        return _profiles[str].profile;
    }

    TrainProfilesModel::TrainProfilesModel(const std::vector<TrainProfilesModel::ProfileWithName> &profiles) {
        std::for_each(profiles.begin(), profiles.end(), [this](auto i){
            _profileNames.push_back(i.name);
            _profiles.insert(std::make_pair<>(i.name, ProfileMapItem{std::prev(_profileNames.end()), i.profile}));
            return i.name;
        });
    }

    ProfileNameList::const_iterator TrainProfilesModel::profileNamesBegin() {
        return _profileNames.cbegin();
    }

    ProfileNameList::const_iterator TrainProfilesModel::profileNamesEnd() {
        return _profileNames.cend();
    }

    ProfileMap &TrainProfilesModel::profileMap() {
        return _profiles;
    }

    ProfileNameList &TrainProfilesModel::profileList() {
        return _profileNames;
    }

    void TrainProfilesModel::setProfile(const std::string &str, const TrainProfile &prof, const std::string &oldStr) {
        if(oldStr != str){
            auto it = _profiles[oldStr].it;
            *(it) = str;
            _profiles.erase(oldStr);
            _profiles[str] = {it, prof};
        } else {
            _profiles[str].profile = prof;
        }
    }

    void TrainProfilesModel::deleteProfile(const std::string &str) {
        _profileNames.erase(_profiles[str].it);
        _profiles.erase(str);
    }

    void TrainProfilesModel::copyModel(const ITrainProfMCopyPtr &other) {
        _profileNames = other->profileList();
        auto profiles = other->profileMap();
        _profiles.clear();
        for(auto it = _profileNames.begin(); it != _profileNames.end(); ++it){
            _profiles.insert(std::make_pair<>(*it, ProfileMapItem{it, profiles[*it].profile}));
        }
    }

    bool TrainProfilesModel::moveDown(const std::string &str) {
        auto it = _profiles[str].it;
        if(it == std::prev(_profileNames.end())){
            return false;
        }
        _profileNames.splice(it, _profileNames, std::next(it));
        return true;
    }

    bool TrainProfilesModel::moveUp(const std::string &str) {
        auto it = _profiles[str].it;
        if(it == _profileNames.begin()){
            return false;
        }
        _profileNames.splice(std::prev(it), _profileNames, it);
        return true;
    }
}
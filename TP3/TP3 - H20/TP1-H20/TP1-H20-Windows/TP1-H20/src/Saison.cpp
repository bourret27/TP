// To do
#include "Saison.h"
// To do
Saison::Saison(): numSaison_(1), nbEpisodesmax_(1)
    // To do
{
}

// To do
Saison::Saison(unsigned int numSaison, unsigned int nbEpisodemax) : numSaison_(numSaison), nbEpisodesmax_(nbEpisodemax)
    // To do
{
}

// To do
Saison::Saison(const Saison& saison) : numSaison_(saison.numSaison_), nbEpisodesmax_(saison.nbEpisodesmax_)

{
    // To do
    for (unsigned i = 0; i < saison.episodes_.size(); ++i)
    {
        episodes_.push_back(std::make_unique<Episode>(*saison.episodes_[i]));
    }
}

// To do
Saison::~Saison()
{
    // To do
    episodes_.clear();
}

// To do
Saison& Saison::operator+=(std::unique_ptr<Episode> episode)
{
    // To do
    size_t indexEpisode = trouverIndexEpisode(episode->getNumEpisode());
    if (indexEpisode > -1)
    {
        episodes_.erase(episodes_.begin() + indexEpisode);
    }
    episodes_.push_back(std::move(episode));
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;
}

// To do
Saison& Saison::operator-=(unsigned int numEpisode)
{
    // To do
    size_t indexEpisode = trouverIndexEpisode(numEpisode);
    if (indexEpisode > -1)
        episodes_.erase(episodes_.begin() + indexEpisode);
    sort(episodes_.begin(), episodes_.end(), Episode::SortByNumEpisode());
    return *this;
}

// To do
bool Saison::operator==(unsigned int numSaison)
{
    // To do
    return numSaison_ == numSaison;
}

// To do
std::ostream& operator<<(std::ostream& os, const Saison& saison)
{
    // To do
    os << "\t" << "Saison "; 
    if (saison.numSaison_ < 10)
    {
        os << "0";
    }
    os << saison.numSaison_ << " " << ':' << " " << saison.episodes_.size() << '/' << saison.nbEpisodesmax_;
    if (saison.episodes_.size() != saison.nbEpisodesmax_)
        os << "(En cours)";
    os << std::endl;
    for (unsigned i = 0; i < saison.episodes_.size(); ++i)
        os << *saison.episodes_[i] << std::endl;
    return os;
    
}

// To do
std::istream& operator>>(std::istream& is, Saison& saison)
{
    // To do
    is >> saison.numSaison_ >> saison.nbEpisodesmax_;
    return is;
}

// To do
unsigned int Saison::getNumSaison() const
{
    // To do
    return numSaison_;
}

// To do
size_t Saison::getNbEpisodes() const
{
   // To do
    return episodes_.size();
}

// To do
size_t Saison::trouverIndexEpisode(unsigned int numEpisode)
{
    // To do
    for (unsigned i = 0; i < episodes_.size(); ++i)
    {
        if (*episodes_[i] == numEpisode)
        {
            return i;
        }
    }
    return -1;
}
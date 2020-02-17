// To do
#include "Episode.h"
// To do
Episode::Episode(): nom_("Episode:01"), duree_("00:00:00"), numEpisode_(1)
// To do
{
}

// To do
Episode::Episode(unsigned int numEpisode, const std::string& nom, const std::string& duree) :
    nom_(nom),
    duree_(duree),
    numEpisode_(numEpisode)
// To do
{
}

// To do
bool Episode::operator==(unsigned int numEpisode)
{
    // To do
    return numEpisode_ == numEpisode;
}

// To do
std::ostream& operator<<(std::ostream& os, const Episode& episode)
{
    // To do
    os << "Episode" << episode.numEpisode_ << ':' << episode.nom_ << '|' << "Durée:" << episode.duree_ << std::endl;
    return os;
    
}

// To do
std::istream& operator>>(std::istream& is, Episode& episode)
{
    // To do
    is >> episode.numEpisode_ >> episode.nom_ >> episode.duree_;
    return is;
    
}

// To do
unsigned int Episode::getNumEpisode() const
{
    // To do
    return numEpisode_;
}
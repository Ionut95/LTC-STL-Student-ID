#pragma once
#include <vector>
#include <string>
#include <stdexcept>

template<class Container, class Song_t>
class DynamicPlaylist
{
public:
    /** @todo Member traits */
    using value_type = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;

    /** @todo Iterators */
    iterator begin() {
        return m_tracklist.begin();
    }
    iterator end() {
        return m_tracklist.end();
    }

    const_iterator cbegin() {
        return m_tracklist.cbegin();
    }

    const_iterator cend() {
        return m_tracklist.cend();
    }

    DynamicPlaylist() = default;

    /** @todo Constructor from two iterators*/
    template<class Iterator>
    DynamicPlaylist(Iterator begin, Iterator end) :
        m_tracklist(begin, end) {}

    /** @todo Set track as currently played from initializer */
    template<class... Args>
    const Song_t& play(Args&&... songData) {
        m_tracklist.emplace_front(std::forward<Args>(songData)...);
        return current();
    }

    /** @todo Set track as currently played from lvalue */
    const Song_t& play(const Song_t& song) {
        m_tracklist.push_front(song);
        return current();
    }

    /** @todo Set track to be played next from initializer */
    template<class... Args>
    void playNext(Args&&... songData) {
        auto it = begin();
        if (it != end()) {
            it++;
        }
        m_tracklist.emplace(it, std::forward<Args>(songData)...);
    }

    /** @todo Set track to be played next from lvalue */
    void playNext(const Song_t& song) {
        auto it = begin();
        if(it != end()) {
            it++;
        }
        m_tracklist.insert(it, song);
    }

    /** @todo Add track to the end of the queue from initializer */
    template<class... Args>
    void add(Args&&... songData) {
        m_tracklist.emplace_back(std::forward<Args>(songData)...);
    }

    /** @todo Add track to the end of the queue from lvalue */
    void add(const Song_t& song) {
        m_tracklist.push_back(song);
    }

    /** @todo Get first track in playlist queue */
    const Song_t& current() const {
        return m_tracklist.front();
    }

    /** @todo Skip to the next track in playlist, remove current */
    void switchNext() {
        if(!hasTracks())
            throw std::out_of_range("Empty list. Please add some songs!");
        m_tracklist.pop_front();
    }

    /** @todo Amount of tracks in playlist */
    size_type count() const {
        return m_tracklist.size();
    }

    /** @todo Checks if playlist has any playable tracks */
    bool hasTracks() const {
        return !m_tracklist.empty();
    }

private:
    Container m_tracklist;
};

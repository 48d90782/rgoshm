#include <boost/interprocess/xsi_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>

void remove_old_memory(const boost::interprocess::xsi_key &key) {
    try {
        boost::interprocess::xsi_shared_memory xsi(boost::interprocess::open_only, key);
        boost::interprocess::xsi_shared_memory::remove(xsi.get_shmid());
    } catch (boost::interprocess::interprocess_exception &err) {
        if (err.get_error_code() != boost::interprocess::not_found_error)
            throw;
    }
}

int main() {

}
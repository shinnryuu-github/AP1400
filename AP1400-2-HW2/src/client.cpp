#include "client.h"
#include "crypto.h"
#include <memory>
#include <random>

Client::Client(std::string id, const Server& server)
: id(id), server(&server){
    std::string public_key, private_key;
    crypto::generate_key(public_key, private_key);
    this->public_key = public_key;
    this->private_key = private_key;
}

std::string Client::get_id() const{
    return this->id;
}

std::string Client::get_publickey() const{
    return this->public_key;
}

double Client::get_wallet() const{
    Server *server = (Server *)this->server;
    return server->get_wallet(this->id);
}

std::string Client::sign(std::string txt) const{
    std::string signature = crypto::signMessage(private_key, txt);
    return signature;
}

bool Client::transfer_money(std::string receiver, double value) const{
    std::string trx = this->get_id() + "-" + receiver + "-" + std::to_string(value);
    if (!((Server *)(this->server))->add_pending_trx(trx, sign(trx)))
        return false;
    return true;
}

size_t Client::generate_nonce() const{
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_int_distribution<size_t> dist(0, std::numeric_limits<size_t>::max());
    return dist(gen);
}
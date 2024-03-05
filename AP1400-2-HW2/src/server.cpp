#include "server.h"
#include "crypto.h"
#include <random>
#include <sstream>

std::vector<std::string> pending_trxs{};

Server::Server()
    : clients() {}

std::shared_ptr<Client> Server::add_client(std::string id){
    bool is_find = false;
    for (auto &[client, wallet] : clients){
        if (client->get_id() == id){
            is_find = true;
            break;
        }
    }
    std::shared_ptr<Client> tmp;
    if (!is_find){
        tmp = std::make_shared<Client>(id, *this);
        clients[tmp] = 5.0;
    }
    else{
        tmp = get_client(id);
        std::random_device rand;
        std::mt19937 gen(rand());
        std::uniform_int_distribution<int> dis(0, 9);
        std::string buffer = tmp->get_id();
        for (size_t i{0}; i < 4; ++i){
            buffer.append(std::to_string(dis(gen)));
        }
        tmp = std::make_shared<Client>(buffer, *this);
    }
    return tmp;
}

std::shared_ptr<Client> Server::get_client(std::string id) const{
    for (auto &[client, wallet] : clients){
        if (client->get_id() == id){
            return client;
        }
    }
    return nullptr;
}

double Server::get_wallet(std::string id){
    auto tmp = get_client(id);
    if (tmp == nullptr)
        return 0.0;
    return clients[tmp];
}

bool Server::parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value){
    for (char ch :trx){
        if (ch == '_'){
            throw std::runtime_error("Invalid transaction");
            return false;
        }
    }
    std::stringstream ss(trx);
    std::getline(ss, sender, '-');
    std::getline(ss, receiver, '-');
    std::string val;
    std::getline(ss, val);
    value = std::stod(val);
    return true;
}

bool Server::add_pending_trx(std::string trx, std::string signature){
    std::string sender, receiver;
    double value;
    try {
        parse_trx(trx, sender, receiver, value);
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    if (get_client(sender) == nullptr || get_client(receiver) == nullptr)
        return false;
    bool authentic = crypto::verifySignature(get_client(sender)->get_publickey(), trx, signature);
    if (!authentic || value > get_wallet(sender))
        return false;
    pending_trxs.push_back(trx);
    return true;
}

class trx{
public:
    std::string sender, receiver;
    double value;
};

size_t Server::mine(){
    std::stringstream ss;
    std::string mempool;
    std::vector<trx> trxs;
    for (auto &str : pending_trxs){
        ss << str;
        std::string sender, receiver;
        double value;
        parse_trx(str, sender, receiver, value);
        trxs.push_back({sender, receiver, value});
    }
    mempool = ss.str();
    size_t resnonce{0};
    while(resnonce == 0){
        for (auto [client, wallet] : clients){
            size_t nonce = client->generate_nonce();
            std::string hash = crypto::sha256(mempool + std::to_string(nonce));
            if (hash.substr(0, 10).find("000") != std::string::npos){
                std::cout << client->get_id() << std::endl;
                resnonce = nonce;
                this->clients[client] += 6.25;
                break;
            }
        }
        if (resnonce != 0)
            break;
    }
    for (auto trx : trxs){
        this->clients[this->get_client(trx.sender)] -= trx.value;
        this->clients[this->get_client(trx.receiver)] += trx.value;
    }
    return resnonce;
}

void show_wallets(const  Server& server){
	std::cout << std::string(20, '*') << std::endl;
	for(const auto& client : server.clients)
		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
	std::cout << std::string(20, '*') << std::endl;
}
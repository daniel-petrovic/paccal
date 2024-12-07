#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <optional>
#include <vector>
#include <ranges>

namespace pacc {
    struct Symbol {
        std::string name;
    };

    struct Env {
        Env(std::shared_ptr<Env> p) : prev{p} {};

        //
        // Get symbols in current block.
        //
        std::vector<Symbol> getSymbols() const {
            std::vector<Symbol> syms;
            for (const auto& s : table)
                syms.push_back(s.second);

            return syms;
        }

        std::optional<Symbol> get(const std::string& name) {
            if (const auto it = table.find(name); it != table.end()) {
                return it->second;
            }

            return prev ? prev->get(name) : std::nullopt;
        }

        void put(const std::string& name, Symbol s) {
            table[name] = std::move(s);
        }

        std::shared_ptr<Env> prev;
        std::unordered_map<std::string, Symbol> table;
    };
}
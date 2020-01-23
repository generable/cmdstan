#ifndef CMDSTAN_ARGUMENTS_MPI_CROSS_CHAIN_SET_OUTPUT_HPP
#define CMDSTAN_ARGUMENTS_MPI_CROSS_CHAIN_SET_OUTPUT_HPP

#include <cmdstan/arguments/categorical_argument.hpp>
#include <cmdstan/arguments/arg_output_file.hpp>
#include <cmdstan/arguments/arg_diagnostic_file.hpp>
#include <cmdstan/arguments/arg_refresh.hpp>
#include <stan/math/mpi/envionment.hpp>

namespace cmdstan {

  void mpi_cross_chain_set_output(argument_parser& parser) {
#ifdef MPI_ADAPTED_WARMUP
    using stan::math::mpi::Session;
    using stan::math::mpi::Communicator;

    // hard-coded nb. of chains
    const int num_chains = 4;
    const Communicator& comm = Session::inter_chain_comm(num_chains);
    string_argument* p = dynamic_cast<string_argument*>(parser.arg("output")->arg("file"));
    std::string chain_output_name = p -> value() + ".mpi." + std::to_string(comm.rank());
    p -> set_value(chain_output_name);
#endif
  }
}
#endif